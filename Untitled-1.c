#include <stdio.h>
#include <stdlib.h>

typedef struct arvore
{
    int info;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

void imprimir_pre_ordem(arvore *a)
{
    if(a != NULL)
    {
        printf("%d", a->info);
        imprimir_pre_ordem(a->esq);
        imprimir_pre_ordem(a->dir);
    }
}

void imprimir_em_ordem(arvore *a)
{
    if(a != NULL)
    {
        imprimir_em_ordem(a->esq);
        printf("%d", a->info);
        imprimir_em_ordem(a->dir);
    }
}

void imprimir_pos_ordem(arvore *a)
{
    imprimir_pos_ordem(a->esq);
    imprimir_pos_ordem(a->dir);
    printf("%d", a->info);
}

int existe (arvore *a)
{
    if()
}
