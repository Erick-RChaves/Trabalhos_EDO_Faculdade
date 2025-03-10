#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arvore
{
    int data;
    struct arvore* esq;
    struct arvore* dir;
}arvore;

arvore* ler_arvore(FILE *arq) //comando 1//
{
    char c;
    int num;
    
    fscanf(arq,"%c",&c);
    fscanf(arq,"%d",&num);
    
    if(num == -1)
    {
        fscanf(arq,"%c",&c);
        return NULL;
    }
    
    else
    {
        arvore* a =(arvore*)malloc(sizeof(arvore));
        a->data = num;
        a->esq = ler_arvore(arq);
        a->dir = ler_arvore(arq);
        fscanf(arq,"%c",&c);
        return a;
    }
}

int altura(arvore* a)
{
    if(a == NULL)
    {
        return 0;
    }

    else
    {
        int he = altura(a->esq);
        int hd = altura(a->dir);

        if(he>hd)
        {
            return he+1;
        }
        else
        {
            return hd+1;
        }

    }
}

void imprimir_pre_ordem(arvore* a)// comando 2.a//
{
    if(a != NULL)
    {
        printf("%d ", a->data);
        imprimir_pre_ordem(a->esq);
        imprimir_pre_ordem(a->dir);
    }
}


void imprimir_em_ordem(arvore* a)//comando2.b//
{
    if(a != NULL)
    {
        imprimir_em_ordem(a->esq);
        printf("%d ", a->data);
        imprimir_em_ordem(a->dir);
    }
} 


void imprimir_pos_ordem(arvore* a)//comando2.c//
{
    if(a != NULL)
    {
        imprimir_pos_ordem(a->esq);
        imprimir_pos_ordem(a->dir);
        printf("%d ", a->data);
    }
}

void print_nivel(arvore* a, int nivel_atual)//auxiliar para o imprimir largura//
{
    if(a != NULL)
    {
        if(nivel_atual == 0)
        {
            printf("%d ", a->data);
        }
        else
        {
            print_nivel(a->esq,nivel_atual - 1 );
            print_nivel(a->dir, nivel_atual - 1);
        }
    }
}

void imprimir_largura(arvore* a)//comando2.d
{
    if(a != NULL)
    {
       int h = altura(a);
       for(int i = 0; i<h;i++)
       {
           print_nivel(a,i);
       }
    }
}

bool existe(arvore* a, int x) //comando3//
{
    if(a != NULL)
    {
        if(a->data == x)
        {
            return true;
        }
        
        else
        {
            int ret = existe(a->esq,x);
            if(ret==1)
            {
                return true;
            }
            return existe(a->dir, x);
        }

    }
     return false;
}



int contar_no(arvore* a)// comando 4//
{
    if(a == NULL)
    {
        return 0;
    }

    return 1 +contar_no(a->esq) +contar_no(a->dir);
}

void imprimir_folha(arvore* a) //comando 5//
{
    if(a == NULL)
    {
        return;
    }

    if(a->esq == NULL && a->dir == NULL)
    {
        printf("%d ", a->data);
        return;
    }

    if(a->esq != NULL)
    {
        imprimir_folha(a->esq);
    }

    if(a->dir != NULL)
    {
        imprimir_folha(a->dir);
    }
}

bool verificar_balanceada(arvore* a, int index, int num_no) // comando 6//
{  
    if(a == NULL)
    {
        return true;
    }
    if(index >= num_no)
    {
        return false;
    }

    return (verificar_balanceada(a->esq, 2*index + 1, num_no) && verificar_balanceada(a->dir, 2*index +2, num_no));

}

bool verificar_cheia(arvore* a) //comando 7//
{
    if(a == NULL)
    {
        return true;
    }
    if(a->esq == NULL && a->dir == NULL)
    {
        return true;
    }
    if((a->esq) && (a->dir))
    {
        return (verificar_cheia(a->esq) && verificar_cheia(a->dir));
    }

    return false;

}

int imprimir_nivel(arvore* a, int x, int contador) //comando 8//
{
    if(a == NULL)
    {
        return -1;
    }

    if(a->data == x)
    {
        return contador;
    }

    int nivel = imprimir_nivel(a->esq, x, contador+1);
    if(nivel != -1)
    {
        return nivel;
    }

    return imprimir_nivel(a->dir, x, contador+1);
}





int main() {
    FILE *arq;
    arvore *a = NULL; 
    int comando=0; 
    int aux,resposta;
    int index = 0, contador = 0;
    
    while(comando != 9) {
        printf("Escolha uma função para realizar:\n");
        printf("1- Ler um arquivo contendo uma árvore(o nome do arquivo deve estar como arvore.txt)\n2- Imprimir uma árvore\n3- Verificar se um elemento X existe na árvore\n");
        printf("4- Contar o número de elementos\n5- Imprimir nós folhas da árvore\n6- Verificar se a árvore está balanceada\n7- Verificar se a árvore é cheia\n");
        printf("8- Imprimir o nível de um nó X\n9- Sair\n");

        scanf("%d", &comando);

        switch (comando) {
            case 1:
                arq = fopen("arvore.txt", "rt");
                if (arq == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    exit(1);
                }
                a = ler_arvore(arq);
                fclose(arq);
                break;

            case 2:
                printf("Digite um número:\n");
                printf("1- Pré-ordem\n2- Em-ordem\n3- Pós-ordem\n4- Em largura\n");
                scanf("%d", &aux);
                switch (aux) {
                    case 1:
                        imprimir_pre_ordem(a);
                        printf("\n");
                        break;
                    case 2:
                        imprimir_em_ordem(a);
                        printf("\n");
                        break;
                    case 3:
                        imprimir_pos_ordem(a);
                        printf("\n");
                        break; 
                    case 4:
                        imprimir_largura(a);
                        printf("\n");
                        break;         
                }
                break;  

            case 3:
                printf("Digite um número:\n");
                scanf("%d", &aux);
                if(existe(a, aux)) {
                    printf("Existe\n");
                } else {
                    printf("Não existe\n");
                }
                break;

            case 4:
                resposta = contar_no(a);
                printf("Existem %d elementos na árvore\n", resposta);
                break;

            case 5:
                imprimir_folha(a);
                printf("\n");
                break;

            case 6:
                aux = contar_no(a);
                if(verificar_balanceada(a, index, aux)) {
                    printf("A árvore é balanceada\n");
                } else {
                    printf("A árvore não é balanceada\n");
                }
                break;

            case 7:
                if(verificar_cheia(a)) {
                    printf("A árvore é cheia\n");
                } else {
                    printf("A árvore não é cheia\n");
                }
                break;

            case 8:
                printf("Digite um número:\n");
                scanf("%d", &aux);

                int nivel = imprimir_nivel(a, aux, contador);
                printf("Está no nível %d\n", nivel);
                break;        
        }
    }
    return 0;
}