#include <stdio.h>
#include <stdlib.h>

void imprimir_combinacao_char(char* string, int pos, int n, int conta_A, char* str_aux) // string aux = {a e i}
{
    int i;
    if(pos == n)
    {
        if(conta_A > n / 2)
        {
            for(i = 0; i < n; i++)
            {
                printf("%c", string[i]);
            }
            printf("\n");
        }
    }
    else
    {
        for(i = 0; i < 3; i++)
        {
            string[pos] = str_aux[i];
            if(str_aux[i] == 'a')
            {
                imprimir_combinacao_char(string, pos + 1, n, conta_A + 1, str_aux);
            }
            else
            {
                imprimir_combinacao_char(string, pos + 1, n, conta_A, str_aux);
            }
        }
    }
}

void imprimircombinacoes(int *vet, int pos, int n, int *vet_aux) //vet_aux = [15,31,55,44]
{
    int i; 
    int contador = 0;
    if(pos == n)
    {
        for(i = 0; i < n; i++)
        {
            contador += vet[i];
        }
        
        if(contador % 2 == 0)
        {
            for(i = 0; i < n; i++)
            {
                printf("%d ", vet[i]);
            }
            printf("\n");
        }
    }
    else
    {
        for(i = 0; i < 4; i++)
        {
            vet[pos] = vet_aux[i];
            imprimircombinacoes(vet, pos + 1, n, vet_aux);
        }
    }
}

void combinacao_moedas(int valor, int *moedas, int n, int index, int *resultado, int conta_moeda)
{
    if(valor == 0)
    {
        printf("%d moedas; temos ", conta_moeda);
        for(int i = 0; i < n; i++)
        {
            if(resultado[i] > 0)
            {
                printf("%d moeda(s) de %d ", resultado[i], moedas[i]);
                if(i < n - 1)
                {
                    printf(", ");
                }
            }
        }
        printf("\n");
        return;
    }

    if(valor < 0 || index == n)
    {
        return;
    }

    resultado[index]++;
    combinacao_moedas(valor - moedas[index], moedas, n, index, resultado, conta_moeda + 1);

    resultado[index]--;
    combinacao_moedas(valor, moedas, n, index + 1, resultado, conta_moeda);
}

int main()
{
    int comando = 0;
    int n;
    int valor;

    int vet_aux[4] = {15, 31, 55, 44};
    int moedas[5] = {50, 25, 10, 5, 1};
    char str_aux[3] = {'a', 'e', 'i'};

    while(comando != 4)
    {
        printf("comandos:\n");
        printf("1. Imprimir combinações de caracteres\n");
        printf("2. Imprimir combinações de números\n");
        printf("3. Imprimir combinações de moedas\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");

        scanf("%d", &comando);

        switch(comando)
        {
            case 1:
            {
                printf("Digite o tamanho da string: ");
                scanf("%d", &n);

                char *string = (char*)malloc((n + 1) * sizeof(char));
                imprimir_combinacao_char(string, 0, n, 0, str_aux);
                free(string);
                break;
            }
            case 2:
            {
                printf("Digite o tamanho do vetor: ");
                scanf("%d", &n);

                int *vetor = (int*)malloc(n * sizeof(int));
                imprimircombinacoes(vetor, 0, n, vet_aux);
                free(vetor);
                break;
            }    
            case 3:
            {
                printf("Digite um valor em centavos: ");
                scanf("%d", &valor);

                int aux = sizeof(moedas) / sizeof(moedas[0]);
                int resultado[aux];
                for(int i = 0; i < aux; i++)
                {
                    resultado[i] = 0;
                }

                combinacao_moedas(valor, moedas, aux, 0, resultado, 0);
                break;
            }    

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Comando inválido. Tente novamente.\n");
                break;
        }
    }

    return 0;
}