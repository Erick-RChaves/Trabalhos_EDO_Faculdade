#include <stdio.h>
#include <stdlib.h>

void imprimir_combinacao_char(char* string, int pos, int n, int conta_A, char* str_aux) {
    if (pos == n) 
    {
        if (conta_A > n / 2) 
        {
            for (int i = 0; i < n; i++) 
            {
                printf("%c", string[i]);
            }
            printf("\n");
        }
    } 
    else 
    {
        for (int i = 0; i < 3; i++) 
        {
            string[pos] = str_aux[i];
            if (str_aux[i] == 'a') 
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

int main()
{
    int n;
    char str_aux[3] = {'a', 'e' ,'i'};
    printf("digite o tamanho da string:");
                scanf("%d",&n);

                char *string = (char*)malloc((n+1) * sizeof(char));
                imprimir_combinacao_char(string, 0, n, 0, str_aux);
                free(string);
    return 0;
}