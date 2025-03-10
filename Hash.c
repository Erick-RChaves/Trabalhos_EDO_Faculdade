#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 53

typedef struct aluno
{
    int mat;
    char nome[100];
    char curso[50];
}Aluno;


typedef struct registro
{
    int info;
    int disponibilidade;
}registro;

int hash(int key, int size)
{
    return key % size;
}

void inicializar(char *nome_arq)
{
    FILE *arq = fopen(nome_arq,"wb");
    registro a;
    int i;
    a.disponibilidade = 1;

    for(i = 0; i < N; i++)
    {
        fwrite(&a, sizeof(registro), 1, arq);
    }

    fclose(arq);
}

int achar_posicao(char *nome_arq, int key)
{
    int posicao = hash(key,N);
    registro a;

    FILE* arq = fopen(nome_arq,"rb");

    fseek(arq,posicao*sizeof(registro),SEEK_SET);
    fread(&a, sizeof(registro), 1, arq);
    while(a.disponibilidade == 0)
    {
        posicao = (posicao+1) % N;
        fseek(arq, posicao*sizeof(registro),SEEK_SET);
        fread(&a,sizeof(registro), 1, arq);
    }

    fclose(arq);
    return posicao;
}

void inserir(char *nome_arq, Aluno aluno)
{
    int posicao = achar_posicao(nome_arq,aluno.mat);
    FILE* arq = fopen(nome_arq,"r+b");

    registro a;
    a.info = aluno.mat;
    a.disponibilidade = 0;

    fseek(arq, posicao*sizeof(registro),SEEK_SET);
    fwrite(&a,sizeof(registro),1,arq);

    fclose(arq);
}

Aluno buscar_aluno(char *nome_arq, int matricula)
{
    int posicao = hash(matricula, N);
    registro a;
    Aluno aluno;
    FILE* arq = fopen(nome_arq, "rb");

    fseek(arq, posicao*sizeof(registro), SEEK_SET);
    fread(&a, sizeof(registro), 1, arq);
    if(a.info == matricula && a.disponibilidade == 0)
    {
        fseek(arq, posicao*sizeof(registro), SEEK_SET);
        fread(&aluno, sizeof(aluno), 1, arq);
        fclose(arq);
        return aluno;
    }
    else
    {
        fclose(arq);
        aluno.mat = -1;
        return aluno;
    }
}

void imprimir_hash(char* nome_arq)
{
    FILE* arq = fopen(nome_arq, "rb");
    registro a;

    printf("posição\tmatricula\tDisponibilidade\n");

    for(int i=0; i<N; i++)
    {
        fread(&a, sizeof(registro), 1, arq);
        printf("%d\t\t%d\t\t%d\n", i,a.info,a.disponibilidade);
    }
}

int main()
{
    char *nome_arq = "alunos.dat";
    int comando = 0;
    Aluno aluno;

    inicializar(nome_arq);

    while(comando != 4)
    {
        printf("1.inserir novo aluno\n2.imprimir as informações de um aluno\n3imprimir a tabela de dispersão\n4.sair");
        scanf("%d", &comando);

        switch(comando)
        {
            case 1:
                printf("Digite a matricula do aluno: ");
                scanf("%d", &aluno.mat);

                printf("Digite o nome do aluno: ");
                scanf("%s", aluno.nome);

                printf("Digite o curso do aluno: ");
                scanf("%s", aluno.curso);

                inserir(nome_arq, aluno);
                printf("Aluno inserido com sucesso!\n");
                break;

            case 2:
                printf("Digite a matricula do aluno: ");
                scanf("%d", &aluno.mat);
                aluno = buscar_aluno(nome_arq, aluno.mat);
                if (aluno.mat != -1) {
                    printf("Aluno encontrado:\n");
                    printf("Matricula: %d\n", aluno.mat);
                    printf("Nome: %s\n", aluno.nome);
                    printf("Curso: %s\n", aluno.curso);
                } else {
                    printf("Aluno nao encontrado.\n");
                }
            case 3:
                imprimir_hash(nome_arq);
                break;
        }
    } 
   return 0;    
}