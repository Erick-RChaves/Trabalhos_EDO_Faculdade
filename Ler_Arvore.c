#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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
    if(a != NULL)
    {
        int he = altura(a->esq);
        int hd = altura(a->dir);
        if(he > hd)
        {
            return he + 1;
        }
        else
        {
            return hd + 1;
        }
    }

    return 0;
} 

arvore* inserir_no(arvore* a, int x) // comando 6//
{
    if(a == NULL)
    {
        a = (arvore*)malloc(sizeof(arvore));
        a->data = x;
        a->esq = NULL;
        a->dir = NULL;
    }
    
    else if(x <= a->data)
    {
        a->esq = inserir_no(a->esq,x);
    }
    else
    {
        a->dir = inserir_no(a->dir,x);
    }
    
    return a;
}

void imprimir_pre_ordem(arvore* a)
{
    if(a != NULL)
    {
        printf("%d ",a->data);
        imprimir_pre_ordem(a->esq);
        imprimir_pre_ordem(a->dir);
    }    
}

void imprimir_em_ordem(arvore* a)
{
    if(a != NULL)
    {
        imprimir_pre_ordem(a->esq);
        printf("%d ",a->data);
        imprimir_pre_ordem(a->dir);
    }    
}

void imprimir_pos_ordem(arvore* a)
{
    if(a != NULL)
    {
        imprimir_pre_ordem(a->esq);
        imprimir_pre_ordem(a->dir);
        printf("%d ",a->data);
    }    
}

void print_nivel(arvore* a, int nivel_atual)//mexer nesse depois//
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

void imprimir_largura(arvore* a)
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

bool existe(arvore* a, int x) // comando 3//
{
    if(a!= NULL)
    {
        if(a->data == x)
        {
            return true;
        }
        else
        {
            if(x<= a->data)
            {
                int ret = existe(a->esq, x);
                if(ret == 1)
                {
                    return true;
                }
            }
            else
            {
                int ret = existe(a->dir,x);
                if(ret == 1)
                {
                    return true;
                }
            }
        }
    }
    
    return false;
}

void imprimir_nivel(arvore* a , int x, int nivel) //tem que começar em zero o nivel// // olhar isso depois//
{
    if(a!= NULL)
    {   
        if(a->data == x)
        {
           printf(" o valor %d esta no nivel %d \n", x, nivel);
        }

        else if(x< a->data)
        {
            imprimir_nivel(a->esq, x, nivel + 1);
        }

        else
        {
            imprimir_nivel(a->dir, x, nivel + 1);
        }

    }  
}

void imprimir_folha_menor(arvore* a, int x)
{
    if(a!= NULL)
    {
        if(a->esq == NULL && a->dir == NULL && a->data < x)
        {
            printf("%d \n ", a->data);
        }

        if(a->esq != NULL)
        {
            imprimir_folha_menor(a->esq,x);
        }

        if(a->dir != NULL)
        {
            imprimir_folha_menor(a->dir, x);
        }
        
    }
}

arvore* no_menor_valor(arvore* a)
{
    arvore* atual = a;

    while(atual && atual != NULL)
    {
        atual = atual->esq;
    }

    return atual;
}

arvore* remover_no(arvore* a, int x)
{
    if(a == NULL)
    {
        return a;
    }

    if(a->data > x)
    {
        a->esq = remover_no(a->esq, x);
    }

    else if(a->data < x)
    {
        a->dir = remover_no(a->dir, x);
    }

    else
    {
        if(a->esq == NULL)
        {
            struct arvore* aux = a->dir;
            free(a);
            return aux; 
        }

        else if(a->dir == NULL)
        {
            struct arvore* aux = a->esq;
            free(a);
            return aux;
        }

        struct arvore* temp = no_menor_valor(a->dir);

        a->data = temp->data;

        a->dir = remover_no(a->dir, temp->data);
    }

    return a;     
} 

int main() {
    FILE *arq;
    arvore *a = NULL; 
    int comando=0; 
    int aux;
    
    while(comando != 8) {
        printf("Escolha uma função para realizar:\n");
        printf("1- Ler um arquivo contendo uma árvore(o nome do arquivo deve estar como arvore.txt)\n2- Imprimir uma árvore\n3- Verificar se um elemento X existe na árvore\n");
        printf("4- Imprimir nivel de um nó X\n5- Imprimir nós folhas menores que X\n6- inserir nó X na arvore\n7- remover nó X da arvore\n");
        printf("8- Sair \n");

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
                printf("Digite um numero: \n");
                scanf("%d",&aux);
                imprimir_nivel(a, aux, 0);
                break;

            case 5:
                printf("Digite um numero: \n");
                scanf("%d", &aux);
                imprimir_folha_menor(a,aux);
                break;

            case 6:
                printf("Digite um numero para adicionar na arvore: \n");
                scanf("%d", &aux);
                a = inserir_no(a, aux);
                break;

            case 7:
                printf("Digite um numero para retirar da arvore: \n");
                scanf("%d", &aux);
                a = remover_no(a, aux);
                break;
        }
    }
    return 0;
}