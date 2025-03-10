#include <stdio.h>
#include<stdlib.h>

void combinacao_moedas(int valor, int *moedas, int n, int index, int *resultado, int conta_moeda)
{
    if (valor == 0)
    {
        printf("representacao com %d moedas; temos ", conta_moeda);
        int primeiro = 1;
        for (int i = 0; i < n; i++)
        {
            if (resultado[i] > 0)
            {
                if (!primeiro)
                {
                    printf(", ");
                }
                printf("%d moeda(s) de %d", resultado[i], moedas[i]);
                primeiro = 0;
            }
        }
        printf("\n");
        return;
    }

    if (valor < 0 || index == n)
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
    int valor;
    printf("Digite um valor em centavos: ");
    scanf("%d", &valor);

    int moedas[] = {1, 5, 10, 25, 50};
    int n = sizeof(moedas) / sizeof(moedas[0]);
    int resultado[n];

    for (int i = 0; i < n; i++)
    {
        resultado[i] = 0;
    }

    combinacao_moedas(valor, moedas, n, 0, resultado, 0);

    return 0;
}