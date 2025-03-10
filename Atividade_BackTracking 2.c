#include<stdio.h>
#include<stdlib.h>

void imprimircombinacoes(int *vet, int pos, int n, int *vet_aux) 
{
    int i;
    int contador = 0;

    if (pos == n) 
    {
        for (i = 0; i < n; i++) 
        {
            contador += vet[i];
        }

        if (contador % 2 == 0) 
        {
            for (i = 0; i < n; i++) 
            {
                printf("%d ", vet[i]);
            }
            printf("\n");
        }
    } 
    else 
    {
        for (i = 0; i < 4; i++) 
        {
            vet[pos] = vet_aux[i];
            imprimircombinacoes(vet, pos + 1, n, vet_aux);
        }
    }
}

int main()
{
    int n;
    int vet_aux[4] = {15, 31, 55, 44};
    printf("digite o tamanho do vetor:");
                scanf("%d",&n);

                int *vetor = (int*)malloc((n)* sizeof(int));
                imprimircombinacoes(vetor, 0, n, vet_aux);
                free(vetor);
    return 0;
}