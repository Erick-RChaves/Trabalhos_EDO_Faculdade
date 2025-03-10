#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct professor // tipo 1
{
    int matricula;
    char nome[20];
    float salario;
}Professor;

typedef struct aluno // tipo 2
{
    int matricula;
    char nome[20];
    char curso[20];
    int ano_ingresso;
}Aluno;

typedef struct _node
{
    int tipo;
    void *item;
    struct _node *next;

}Node;

void inicializar_lista(Node** head)
{
   *head = NULL;
}

void inserir_pessoa(Node** head, void *info, int tipo_pessoa)
{
    Node *new_node = (Node*)malloc(sizeof(Node));

    new_node->tipo = tipo_pessoa;
    new_node->next = (*head);
    new_node->item = info;

    *head = new_node;
}

void remover_matricula(Node** head, int matricula)
{
    Node *current = *head;
    Node *prev = NULL;

    while(current != NULL)
    {
        int current_matricula;
        if(current->tipo == 1)
        {
            current_matricula = ((Professor*)(current->item))->matricula;
        }
        else if(current->tipo == 2)
        {
            current_matricula = ((Aluno*)(current->item))->matricula;
        }
        else
        {
            current = current->next;
            continue;
        }

        if(current_matricula == matricula)
        {
            if(prev == NULL)
            {
                *head = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            free(current->item);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void buscar_matricula(Node **head, int matricula)
{
    Node *current = *head;

    while (current != NULL)
    {
        if (current->tipo == 1)
        {
           Professor *prof = ((Professor*)(current->item));
           if(prof->matricula == matricula)
           {
                printf("matricula: %d \nnome: %s \nsalario: R$ %.2f\n", prof->matricula, prof->nome, prof->salario);
                break;
           }
        }

        else if(current->tipo == 2)
        {
            Aluno *aluno = ((Aluno*)(current->item));
            if(aluno->matricula == matricula)
            {
                printf("matricula: %d \nnome: %s \ncurso: %s \nano de ingresso: %d\n", aluno->matricula, aluno->nome, aluno->curso, aluno->ano_ingresso);
                break;
            }
        }
        current = current->next;
    }
    
}

int contar_aluno(Node **head, char *curso_procurado)
{
    Node *current = *head;
    int contador = 0;

    while(current != NULL)
    {
        if(current->tipo == 2)
        {
            Aluno *aluno = ((Aluno*)(current->item));
            if(strcmp(aluno->curso, curso_procurado) == 0)
            {
                contador++;
            }
        }

        current = current->next;
    }    
    
    return contador;
}

void maior_salario(Node **head)
{
    Node *current = *head;
    float maior_salario = 0;

    while(current != NULL) // primeiro loop para achar o maior valor
    {
        if(current->tipo == 1)
        {
            Professor *prof = ((Professor*)(current->item));
            if(prof->salario > maior_salario)
            {
               maior_salario = prof->salario;
            } 
        }
      current = current->next;
    }

    current = *head; //resetando o current

    while (current != NULL) //segundo loop para imprimir os professores com o maior salario
    {
        if(current->tipo == 1)
        {
            Professor *prof = ((Professor*)(current->item));
            if(maior_salario == prof->salario)
            {
                printf("matricula:%d \nnome:%s \nsalario:%2.2f", prof->matricula,prof->nome,prof->salario);
            }
        }
        current = current->next;
    } 
}

void liberar_memoria(Node* head)
{
    Node* current = head;
    Node* temp;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp->item);
        free(temp);
    }
}

int main()
{
    Node *head = NULL;
    inicializar_lista(&head);
    int comando = 0;
    int aux;
    char string[20];
    int tipo;

    while(comando != 6)
    {
        printf("Escolha uma função para realizar:\n");
        printf("1- inserir uma pessoa na lista\n2- remover uma pessoa pela matricula\n3- buscar uma pessoa\n");
        printf("4- contar o numero de alunos de determinado curso\n5- imprimir os professores de maior salario\n6- sair\n");
        scanf("%d",&comando);

        switch (comando)
        {
        case 1:
            printf("digite para adicionar: \n1-professor\n2-aluno");
            scanf("%d",&tipo);
            if(tipo == 1)
            {
                Professor *prof = (Professor*)malloc(sizeof(Professor));
                printf("digite a matricula do professor:\n");
                scanf("%d", &prof->matricula);

                printf("digite o nome do professor\n");
                scanf("%s", prof->nome);

                printf("digite o salario\n");
                scanf("%f", &prof->salario);

                inserir_pessoa(&head, prof, 1);
            }
            else if(tipo == 2)
            {
                Aluno *aluno  = (Aluno*)malloc(sizeof(Aluno));
                printf("digite a matricula do aluno:\n");
                scanf("%d",&aluno->matricula);

                printf("digite o nome do aluno:\n");
                scanf("%s",aluno->nome);

                printf("digite o curso do aluno:\n");
                scanf("%s",aluno->curso);

                printf("digite o ano de ingresso:\n");
                scanf("%d",&aluno->ano_ingresso);

                inserir_pessoa(&head, aluno, 2);
            }
            break;
        
        case 2:
            printf("digite a matricula de quem deseja retirar:");
            scanf("%d",&aux);
            remover_matricula(&head, aux);
            break;

        case 3:
            printf("digite a matricula de quem deseja procurar");
            scanf("%d", &aux);
            buscar_matricula(&head, aux);
            break;

        case 4:
            printf("digite o nome do curso: ");
            scanf("%s",string);
            int contador = contar_aluno(&head, string);
            printf("%d aluno(s)", contador);
            break;

        case 5:
            maior_salario(&head);
            break;

        case 6:
            liberar_memoria(head);
            break;
        }

    }
    return 0;
}    