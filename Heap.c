#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NMAX 100
int total_elementos = 0; // Variavel global//

int indice_filho_esq(int x)
{
    int indice = (2*x)+1;
    if(x>=total_elementos || indice >= total_elementos)
    {
        return -1;
    }
    else
    {
        return indice;
    }
}

int indice_filho_dir(int x)
{
    int indice = (2*x)+2;
    if(x>= total_elementos || indice >= total_elementos)
    {
        return -1;
    }
    else
    {
        return indice;
    }
}

int indice_pai(int x)
{
    int indice = (int)floor((x-1)/2);
    if(x <= 0 || x>= total_elementos)
    {
        return -1;
    }
    else
    {
        return indice;
    }
}

void ajustar_subindo(int* heap, int pos)
{
    if(pos != -1)
    {
        int pai = indice_pai(pos);
        if(pai != -1)
        {
            if(heap[pos] < heap[pai])
            {
                int aux = heap[pos];
                heap[pos] = heap[pai];
                heap[pai] = aux;
                ajustar_subindo(heap, pai);
            }
        }
    }
}

void inserir(int* heap, int x)
{
    heap[total_elementos] = x;
    total_elementos++;

    ajustar_subindo(heap, total_elementos-1);
 
}

void ajustar_descendo(int* heap, int pos) {
    if (pos != -1 && indice_filho_esq(pos) != -1) 
    {
        int indice_maiorfilho = indice_filho_esq(pos);
        if (indice_filho_dir(pos) != -1 && heap[indice_filho_dir(pos)] < heap[indice_maiorfilho]) 
        {
            indice_maiorfilho = indice_filho_dir(pos);
        }
        if (heap[indice_maiorfilho] < heap[pos]) 
        {
            int aux = heap[pos];
            heap[pos] = heap[indice_maiorfilho];
            heap[indice_maiorfilho] = aux;
            ajustar_descendo(heap, indice_maiorfilho);
        }
    }
}

int remover(int *heap)
{
    if(total_elementos == 0)
    {
        return -1;
    }
    else
    {
        int retorno = heap[0];
        heap[0] = heap[total_elementos -1];
        total_elementos--;
        ajustar_descendo(heap,0);
        return retorno;
    }
}

void imprimir_heap(int* heap, int N)
{
    printf("elementos da heap:");
    for(int i = 0; i<N; i++)
    {
        printf("%d|",heap[i]);
    }
    printf("\n");
}


int main()
{
    int heap[NMAX];
    int comando = 0;
    int y,x;

    while(comando != 4)
    {
        printf("1 inserir elemento\n2 remover elemento\n3 imprimir o heap\n4 sair\n");
        scanf("%d", &comando);

        switch(comando)
        {
            case 1:
                printf("digite um numero inteiro X para adicionar:\n");
                scanf("%d",&x);
                inserir(heap,x);
            break;

            case 2:
                y = remover(heap);
                printf("elemento removido: %d\n",y);
            break;

            case 3:
                imprimir_heap(heap,total_elementos);
            break;
        }
    }
    return 0;
}