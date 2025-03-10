#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct lista
{
    int data;
    struct lista* next;
}lista;

lista* add_lista(lista* l, int x) //função para criar/adicionar a lista//
{
    if(l == NULL)
    {
        lista* node = (lista*)malloc(sizeof(lista));
        node->data = x;
        node->next = NULL;
        return node;
    }
    
    else
    {
        l->next = add_lista(l->next, x);
        return l;
    }
}


void print_list(lista* l)// função para printar a lista//
{
    if(l == NULL)
    {
        return;
    }
    
    else
    {
        printf("%d ",l->data);
        return print_list(l->next);
    }
}



int soma_lista(lista* l, int x)//função para somar os valores dos nos da lista
{
    if(l == NULL)
    {
        return x;
    }
    

    else
    {
        x = x + l->data;
        return soma_lista(l->next, x);
    }
}


int ocorrencia_lista(lista* l, int x)//função pra contar a qtd de vezes que aparece o numero//
{
    if(l == NULL)
    {
        return 0;
    }
    
    else if (l->data != x)
     {
        return ocorrencia_lista(l->next,x);
     }
    
    else if(l->data == x)
    {
        return 1 + ocorrencia_lista(l->next, x);
    }

    return 0;
}



lista* tirar_no(lista* l, int x)
{
    if (l == NULL)
    {
        return NULL;
    }
        
    if (l->data == x)
    {
        lista * aux = l->next;
        free(l);
        return tirar_no(aux, x);
    }

    l->next = tirar_no(l->next, x);
    return l;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    lista* l = NULL;

    srand(time(NULL));

    printf("lista gerada : ");

    for(int i = 0; i<10;i++)
    {
        l = add_lista(l, rand() % 9 + 1); //cria uma lista com valores aleatorios//
    }
    
    print_list(l); //printa a lista//
    
    
    int soma = soma_lista(l,0);
    printf("\na soma de todos os elementos da lista = %d", soma);
    
    
    int x = rand() % 9 + 1; //gera um numero aleatorio para procurar//
    
    
    printf("\nnúmero aleatório gerado: %d    quantidade de ocorrencias dele na lista: %d\n",x, ocorrencia_lista(l,x));
    
    int y;
    printf("digite o número que deseja retirar da lista: ");
    scanf("\n%d",&y);

    printf("lista atualizada: ");
    
    l = tirar_no(l,y);
    print_list(l);
} 