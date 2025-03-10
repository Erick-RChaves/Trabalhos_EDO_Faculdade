#include <stdlib.h>
#include <stdio.h>

typedef struct avl
{
    int data;
    int FB;
    struct avl *esq;
    struct avl *dir;
} AVL;

int altura(AVL* a)
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

void ajustaFB(AVL *a)
{
    if(a != NULL)
    {
        a->FB = altura(a->dir) - altura(a->esq);
        ajustaFB(a->esq);
        ajustaFB(a->dir);
    }
}

AVL* ler_arvore(FILE *arq)
{
    char c;
    int num;
    
    fscanf(arq, " %c", &c);
    fscanf(arq, "%d", &num);
    
    if(num == -1)
    {
        fscanf(arq, "%c", &c);
        return NULL;
    }
    else
    {
        AVL* a = (AVL*)malloc(sizeof(AVL));
        a->data = num;
        a->esq = ler_arvore(arq);
        a->dir = ler_arvore(arq);
        a->FB = 0;
        fscanf(arq, "%c", &c);
        return a;
    }
}

AVL* ler_AVL(FILE *arq)
{
    AVL* a = ler_arvore(arq);
    ajustaFB(a);
    return a;
}

int existe(AVL *a, int x)
{
    if(a == NULL)
    {
        return 0;
    }    
    else if(a->data == x)
    {
        return 1;
    }    
    else if(a->data < x)
    {
        return existe(a->dir, x);
    }    
    else
    {
        return existe(a->esq, x);
    }    
}

void imprimir_pre_ordem(AVL* a)
{
    if(a != NULL)
    {
        printf("%d ", a->data);
        imprimir_pre_ordem(a->esq);
        imprimir_pre_ordem(a->dir);
    }
}

void imprimir_em_ordem(AVL* a)
{
    if(a != NULL)
    {
        imprimir_em_ordem(a->esq);
        printf("%d ", a->data);
        imprimir_em_ordem(a->dir);
    }
}

void imprimir_pos_ordem(AVL* a)
{
    if(a != NULL)
    {
        imprimir_pos_ordem(a->esq);
        imprimir_pos_ordem(a->dir);
        printf("%d ", a->data);
    }
}

void print_nivel(AVL* a, int nivel_atual)
{
    if(a != NULL)
    {
        if(nivel_atual == 0)
        {
            printf("%d ", a->data);
        }    
        else
        {
            print_nivel(a->esq, nivel_atual - 1);
            print_nivel(a->dir, nivel_atual - 1);
        }
    }
}

void imprimir_largura(AVL* a)
{
    if(a != NULL)
    {
        int h = altura(a);
        for(int i = 0; i < h; i++)
        {
            print_nivel(a, i);
        }    
    }
}

void imprimir_nivel(AVL* a, int x, int nivel)
{
    if(a != NULL)
    {   
        if(a->data == x)
        {
            printf(" o valor %d esta no nivel %d \n", x, nivel);
        }    
        else if(x < a->data)
        {
            imprimir_nivel(a->esq, x, nivel + 1);
        }    
        else
        {
            imprimir_nivel(a->dir, x, nivel + 1);
        }    
    }  
}

void imprimir_folha_menor(AVL* a, int x) // ver depois
{
    if(a != NULL)
    {
        if(a->esq == NULL && a->dir == NULL && a->data < x)
        {
            printf("%d \n ", a->data);
        }    

        if(a->esq != NULL)
        {
            imprimir_folha_menor(a->esq, x);
        }    

        if(a->dir != NULL)
            imprimir_folha_menor(a->dir, x);
    }
}

AVL* Rotacao_Esq_Simples(AVL* a)
{
    AVL* b = a;
    AVL* c = a->dir;

    b->dir = c->esq;
    c->esq = b;

    if(c->FB == 1)
    {
        b->FB = 0;
        c->FB = 0;
    }
    else
    {
        b->FB = 1;
        c->FB = -1;
    }

    a = c;
    return a;
}

AVL* Rotacao_Esq_Dupla(AVL* a)
{
    AVL* b = a;
    AVL* c = a->dir;
    AVL* d = c->esq;

    c->esq = d->dir;
    b->dir = d->esq;

    d->esq = b;
    d->dir = c;

    switch (d->FB)
    {
        case -1:
            b->FB = 0;
            c->FB = 1;
            break;
        case 0:
            b->FB = 0;
            c->FB = 0;
            break;
        case +1:
            b->FB = -1;
            c->FB = 0;
            break;
    }

    d->FB = 0;

    a = d;
    return a;
}

AVL* Rotacao_Esq(AVL* a)
{
    if(a->dir->FB == -1)
    {
        return Rotacao_Esq_Dupla(a);
    }    
    else
    {
        return Rotacao_Esq_Simples(a);
    }    
}

AVL* Rotacao_Dir_Simples(AVL* a)
{
    AVL* b = a->esq;
    AVL* c = a;

    c->esq = b->dir;
    b->dir = c;

    if (b->FB == -1)
    {
        b->FB = 0;
        c->FB = 0;
    }
    else
    {
        b->FB = 1;
        c->FB = -1;
    }

    a = b;
    return a;
}

AVL* Rotacao_Dir_Dupla(AVL* a)
{
    AVL* b = a;
    AVL* c = b->esq;
    AVL* d = c->dir;

    b->esq = d->dir;
    c->dir = d->esq;
    d->esq = c;
    d->dir = b;

    switch(d->FB)
    {
        case -1:
            c->FB = 0;
            b->FB = 1;
            break;
        case 0:
            c->FB = 0;
            b->FB = 0;
            break;
        case +1:
            c->FB = -1;
            b->FB = 0;
            break;
    }

    d->FB = 0;

    a = d;
    return a;
}

AVL* Rotacao_Dir(AVL* a)
{
    if(a->esq->FB == 1)
    {
        return Rotacao_Dir_Dupla(a);
    }    
    else
    {
        return Rotacao_Dir_Simples(a);
    }    
}

AVL* inserir(AVL* a, int x, int* HX)
{
    if(a == NULL)
    {
        a = (AVL*)malloc(sizeof(AVL));
        a->data = x;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *HX = 1;
    }
    else
    {
        if(x <= a->data)
        {
            a->esq = inserir(a->esq, x, HX);
            if(*HX == 1)
            {
                switch(a->FB)
                {
                    case -1:
                        a = Rotacao_Dir(a);
                        *HX = 0;
                        break;
                    case 0:
                        a->FB = -1;
                        *HX = 1;
                        break;
                    case +1:
                        a->FB = 0;
                        *HX = 0;
                        break;
                }
            }
        }
        else
        {
            a->dir = inserir(a->dir, x, HX);
            if(*HX == 1)
            {
                switch(a->FB)
                {
                    case -1:
                        a->FB = 0;
                        *HX = 0;
                        break;
                    case 0:
                        a->FB = +1;
                        *HX = 1;
                        break;
                    case +1:
                        a = Rotacao_Esq(a);
                        *HX = 0;
                        break;
                }
            }
        }
    }
    return a;
}

AVL* Remover(AVL* a, int x, int* HX)
{
    if(a != NULL)
    {
        if(a->data == x)
        {
            if(a->esq == NULL && a->dir == NULL) //remover folha//
            {
                free(a);
                *HX = 1;
                return NULL;
            }
            else if(a->esq == NULL || a->dir == NULL) //remover com um lado nulo//
            {
                AVL* aux;
                if(a->esq == NULL)
                    aux = a->dir;
                else
                    aux = a->esq;

                free(a);
                *HX = 1;
                return aux;
            }
            else //remover com os dois nulos//
            {
                AVL* maior_esq = a->esq;
                while(maior_esq->dir != NULL)
                    maior_esq = maior_esq->dir;

                a->data = maior_esq->data;
                a->esq = Remover(a->esq, a->data, HX);   

                if(*HX == 1)
                {
                    switch(a->FB)
                    {
                        case -1:
                            a->FB = 0;
                            *HX = 1;
                            break;
                        case 0:
                            a->FB = 1;
                            *HX = 0;
                            break;
                        case +1:
                            {
                                int aux = a->dir->FB; 
                                a = Rotacao_Esq(a);
                                if(aux == 0)
                                    *HX = 0;
                                else
                                    *HX = 1;
                                break; 
                            }            
                    }
                }
            }
        }
        else if (x < a->data)
        {
            a->esq = Remover(a->esq, x, HX);
            if(*HX == 1)
            {
                switch(a->FB)
                {
                    case -1:
                        a->FB = 0;
                        *HX = 1;
                        break;
                    case 0:
                        a->FB = 1;
                        *HX = 0;
                        break;
                    case +1:
                        {
                            int aux = a->dir->FB;
                            a = Rotacao_Esq(a);
                            if(aux == 0)
                                *HX = 0;
                            else
                                *HX = 1;
                        }           
                }
            }
        }
        else
        {
            a->dir = Remover(a->dir, x, HX);
            if(*HX == 1)
            {
                switch(a->FB)
                {
                    case -1:
                        {
                            int aux = a->esq->FB;
                            a =  Rotacao_Dir(a);

                            if(aux == 0)
                                *HX = 0;
                            else
                                *HX = 1;
                            break;
                        }
                    case 0:
                        a->FB = -1;
                        *HX = 0;
                        break;
                    case +1:
                        a->FB = 0;
                        *HX = 1;    
                }
            }
        }
    }
    return a; 
}

void liberar_arvore(AVL* a)
{
    if(a!= NULL)
    {
        liberar_arvore(a->esq);
        liberar_arvore(a->dir);
        free(a);
    }    
}

int main() {
    FILE *arq;
    AVL *a = NULL; 
    int comando=0, HX = 0; 
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
                a = inserir(a, aux, &HX);
                break;

            case 7:
                printf("Digite um numero para retirar da arvore: \n");
                scanf("%d", &aux);
                a = Remover(a, aux, &HX);
                break;
            case 8:
                liberar_arvore(a);
                a = NULL;
                break;
        }
    }
    return 0;
}