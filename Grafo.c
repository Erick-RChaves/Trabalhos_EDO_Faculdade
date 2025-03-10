#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define N 16

typedef struct lista
{
    int destino;
    int custo;
    struct lista *prox;
}lista;

void inicializar_grafo(lista **g, int n)
{
    int i;
    for(i=0; i<=n; i++)
    {
        g[i] = NULL;
    }
}

lista *inserir_lista(lista *l, int d, int c)
{
    lista *no = (lista*)malloc(sizeof(lista));
    no->destino = d;
    no->custo = c;
    no->prox = l;
    return no;
}

void inserir_aresta(lista **g, int origem, int destino, int custo)
{
    g[origem] = inserir_lista(g[origem], destino, custo);
}

void remover_aresta(lista **g, int origem, int destino)
{
    lista *aux = g[origem];
    lista *prev= NULL; //vem de previous

    while(aux !=NULL)
    {
        if(aux->destino == destino)
        {
            if(prev == NULL)
            {
                g[origem] = aux->prox;
            }
            else
            {
                prev->prox = aux->prox;
            }
            free(aux);
            return;
        }
        prev = aux;
        aux = aux->prox;
    }
    printf("aresta(%d -> %d) nao encontrada.\n",origem,destino);
}

void imprimir_lista(lista *l)
{
    if(l != NULL)
    {
        printf("-(%d, %d)",l->destino,l->custo);
        imprimir_lista(l->prox);
    }
}

void imprimir_grafo(lista **g, int n)
{
    int i;
    printf("grafo:");
    for(i=1; i<=n; i++)
    {
        printf("\n\t%d",i);
        imprimir_lista(g[i]);
    }
}

int grau_entrada(lista **g, int vertice, int n) // vertice = i do for   
{
    int grau = 0;
    for(int i=1; i<=n; i++)
    {
        lista *aux = g[i];
        while(aux != NULL)
        {
            if(aux->destino == vertice)
            {
                grau++;
            }
            aux = aux->prox;
        }
    }
    return grau;
}

int grau_saida(lista **g, int vertice)
{
    int grau = 0;
    lista *aux = g[vertice];
    while(aux != NULL)
    {
        grau++;
        aux = aux->prox;
    }
    return grau;
}

int verificar_completo(lista **g, int n)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if (i!= j)
            {
                lista *aux = g[i];
                int achou = 0;
                while(aux != NULL)
                {
                    if(aux->destino != j)
                    {
                        achou = 1;
                        break;
                    }
                    aux = aux->prox;
                }
                if (!achou)
                {
                    return 0;
                }
            }
            
        }
    }
    return 1;
}

int existe(int *vet, int vertice, int pos)
{
    for(int i=0; i<pos; i++)
    {
        if(vet[i] == vertice)
        {
            return 1;
        }
    }
    return 0;
}

void caminhos(lista **g, int b, int *vet, int pos)
{
    if(vet[pos-1] == b)
    {
        int i;
        printf("\n");
        for(i=0; i<pos;i++)
        {
            printf("%d", vet[i]);
        }
    }
    else
    {
        lista *p = g[vet[pos-1]];
        while(p != NULL)
        {
            if(!existe(vet, p->destino, pos))
            {
                vet[pos] = p->destino;
                caminhos(g, b, vet, pos+1);
            }
            p = p ->prox;
        }
    }

}

void imprimir_todos_caminhos(lista **g, int origem, int destino, int n)
{
    int *vet = (int *)malloc(n* sizeof(int));
    for(int i=0; i<n; i++)
    {
        vet[i] = -1;
    }
    vet[0] = origem;
    caminhos(g, destino, vet, 1);
    free(vet);
}

int min_dist(int dist[], int visitado[], int n) {
    int min = INT_MAX, min_index;
    for(int v = 0; v < n; v++) {
        if(visitado[v] == 0 && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void dijkstra(lista **g, int origem, int destino, int n) 
{
    int dist[n]; 
    int visitado[n]; 

    for(int i = 0; i < n; i++) {
        dist[i] = INT_MAX, visitado[i] = 0;
    }

    dist[origem] = 0;

    int caminho[n];
    for(int i = 0; i < n; i++) {
        caminho[i] = -1;
    }
    caminho[origem] = origem;

    for(int count = 0; count < n - 1; count++) {
        int u = min_dist(dist, visitado, n);

        visitado[u] = 1;
        lista *p = g[u];
        while(p != NULL) {
            int v = p->destino;

            if(!visitado[v] && dist[u] != INT_MAX && dist[u] + p->custo < dist[v]) {
                dist[v] = dist[u] + p->custo;
                caminho[v] = u;
            }
            p = p->prox;
        }
    }

    if(dist[destino] == INT_MAX) {
        printf("Não existe caminho do vértice %d ao vértice %d\n", origem, destino);
        return;
    }

    printf("Distância mínima do vértice %d ao vértice %d é %d\n", origem, destino, dist[destino]);
    printf("Caminho: ");

    int caminho_reverso[n];
    int j = 0;
    for(int v = destino; v != -1; v = caminho[v]) {
        caminho_reverso[j++] = v;
    }
    for(int i = j - 1; i >= 0; i--) {
        printf("%d ", caminho_reverso[i]);
    }
    printf("\n");
}

void imprimir_caminho(int *caminho, int origem, int destino) 
{
    if (caminho[destino] == -1) {
        printf("Não existe caminho do vértice %d ao vértice %d\n", origem, destino);
        return;
    }

    int stack[N];
    int top = -1;
    for (int v = destino; v != -1; v = caminho[v]) {
        stack[++top] = v;
    }

    printf("Caminho de menor custo do vértice %d ao vértice %d: ", origem, destino);
    while (top >= 0) {
        printf("%d ", stack[top--]);
    }
    printf("\n");
}

int main()
{
    lista **g;
    int destino, origem, custo;
    int comando = 0;

     printf("Escolha uma função para realizar:\n");
        printf("1- inserir aresta no grafo\n2- ramover uma aresta do grafo\n3- imprimir grafo\n");
        printf("4- Imprimir graus de entrada e saida do vertice\n5- verificar se o grafo e completo\n6- imprimir todos os caminhos\n7- imprimir o caminho mais curto\n");
        printf("8- imprimir o caminho de menor custo \n9- sair");
    scanf("%d",&comando);

    while(comando != 9)
    {
        g = (lista**)malloc((N+1)*sizeof(lista*)); // iniciar vetor dinâmico

        inicializar_grafo(g, N);

        switch(comando)
        {
            case 1:
                printf("digite o origem, a destino e o custo da aresta a ser adicionada:\n");
                scanf("%d %d %d",&origem, &destino, &custo);

                inserir_aresta(g, origem, destino, custo);
                break;

            case 2:
                printf("digite a origem e o destino da aresta a ser removida:\n "); // funcao retirar aresta
                scanf("%d %d", &origem, &destino);
                remover_aresta(g, origem, destino);
                break;    

            case 3:
                imprimir_grafo(g, 3); // função imprimir grafo
                break;

            case 4:
                for(int i=0; i<=N;i++)
                {
                    int grau_E = grau_entrada(g, i, N);
                    int grau_S = grau_saida(g,i);
                    printf("Grau de entrada do vertice %d: grau de entrada: %d \ngrau de saida:%d", i,grau_E,grau_S);
                }
                break;  

            case 5:
                if(verificar_completo(g, N))
                {
                    printf("o grafo é completo\n");
                }
                else
                {
                    printf("não é completo\n");
                }
                break;

            case 6:
                printf("Digite a origem e o destino para imprimir todos os caminhos:\n");
                scanf("%d %d", &origem, &destino);
                imprimir_todos_caminhos(g, origem, destino, N);
                break;    

            case 7:
                printf("Digite a origem e o destino para encontrar o caminho mais curto:\n");
                scanf("%d %d", &origem, &destino);
                dijkstra(g, origem, destino, N);
                break; 

            case 8:
            printf("Digite a origem e o destino para encontrar o caminho mais curto:\n");
                scanf("%d %d", &origem, &destino);

                int dist[N];
                int visitado[N];
                int caminho[N];

                for(int i = 0; i < N; i++) {
                    dist[i] = INT_MAX;
                    visitado[i] = 0;
                    caminho[i] = -1;
                }

                dist[origem] = 0;

                for(int count = 0; count < N - 1; count++) {
                    int u = min_dist(dist, visitado, N);
                    visitado[u] = 1;

                    lista *p = g[u];
                    while(p != NULL) {
                        int v = p->destino;

                        if(!visitado[v] && dist[u] != INT_MAX && dist[u] + p->custo < dist[v]) {
                            dist[v] = dist[u] + p->custo;
                            caminho[v] = u;
                        }
                        p = p->prox;
                    }
                }

                imprimir_caminho(caminho, origem, destino);
                break;       

            case 9:
                for (int i = 0; i <= N; i++) 
                {
                    lista *aux = g[i];
                    while (aux != NULL) 
                    {
                        lista *temp = aux;
                        aux = aux->prox;
                        free(temp);
                    }
                } 
                break;   
        }

    }
  

    return 0;
}