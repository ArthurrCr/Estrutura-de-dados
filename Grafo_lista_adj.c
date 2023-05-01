// Lista de Adjacência
#include <stdio.h>
#include <stdlib.h>

typedef struct NoListaAdj {
    int destino; // índice do vértice de destino
    struct NoListaAdj* proximo; // ponteiro para o próximo nó
} NoListaAdj;

typedef struct ListaAdj {
    NoListaAdj* cabeca; // ponteiro para a cabeça da lista
} ListaAdj;

typedef struct Grafo {
    int num_vertices; // número de vértices
    ListaAdj* vetor; // vetor de listas de adjacência
} Grafo;

NoListaAdj* novoNoListaAdj(int destino) {
    NoListaAdj* novoNo = (NoListaAdj*)malloc(sizeof(NoListaAdj)); // aloca memória para o novo nó
    novoNo->destino = destino; // atribui o índice do vértice de destino
    novoNo->proximo = NULL; // define o próximo nó como NULL
    return novoNo;
}

Grafo* criarGrafo(int num_vertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo)); // aloca memória para o grafo
    grafo->num_vertices = num_vertices; // define o número de vértices

    grafo->vetor = (ListaAdj*)malloc(num_vertices * sizeof(ListaAdj));  

    for (int i = 0; i < num_vertices; ++i) {
        grafo->vetor[i].cabeca = NULL; // define a cabeça de cada lista como NULL
    }

    return grafo;
}

void adicionarAresta(Grafo* grafo, int origem, int destino) {
    NoListaAdj* novoNo = novoNoListaAdj(destino); // cria um novo nó para a lista de adjacência
    novoNo->proximo = grafo->vetor[origem].cabeca; // define o próximo nó como a cabeça da lista
    grafo->vetor[origem].cabeca = novoNo; // define o novo nó como a cabeça da lista

    novoNo = novoNoListaAdj(origem); // cria um novo nó para a lista de adjacência
    novoNo->proximo = grafo->vetor[destino].cabeca; // define o próximo nó como a cabeça da lista
    grafo->vetor[destino].cabeca = novoNo; // define o novo nó como a cabeça da lista
}

void carregarGrafoDeArquivo(Grafo* grafo, char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r"); // abre o arquivo para leitura

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    int num_vertices; // número de vértices
    fscanf(arquivo, "%d", &num_vertices); // lê o número de vértices do arquivo

    *grafo = *criarGrafo(num_vertices); // cria o grafo

    int origem, destino;
    while (fscanf(arquivo, "%d %d", &origem, &destino) == 2) {
        adicionarAresta(grafo, origem, destino); // adiciona a aresta no grafo
    }

    fclose(arquivo);
}

void imprimirGrafo(Grafo* grafo) {
    printf("Lista de Adjacência:\n");
    for (int i = 0; i < grafo->num_vertices; i++) {
        NoListaAdj* atual = grafo->vetor[i].cabeca; // define o nó atual como a cabeça da lista
        printf("%d: ", i);  
        while (atual != NULL) { // percorre a lista de adjacência
            printf("%d -> ", atual->destino); // imprime o índice do vértice de destino
            atual = atual->proximo; // define o próximo nó como o nó atual
        }
        printf("NULL\n");
    }
}

//Busca em Largura BFS
void bfs(Grafo* grafo, int vertice_inicial) {
    int* visitado = (int*)malloc(grafo->num_vertices * sizeof(int));
    for (int i = 0; i < grafo->num_vertices; i++) { // define todos os vértices como não visitados
        visitado[i] = 0; // 0 = não visitado, 1 = visitado
    }  

    ListaAdj fila; // cria uma fila
    fila.cabeca = NULL; // define a cabeça da fila como NULL

    visitado[vertice_inicial] = 1; // define o vértice inicial como visitado
    printf("Visitando vertice %d\n", vertice_inicial); // imprime o vértice inicial
    NoListaAdj* atual = grafo->vetor[vertice_inicial].cabeca; // define o nó atual como a cabeça da lista de adjacência do vértice inicial

    while (atual != NULL) { 
        if (!visitado[atual->destino]) { // adiciona o vértice apenas se ainda não foi visitado
            visitado[atual->destino] = 1; // define o vértice como visitado
            printf("Visitando vertice %d\n", atual->destino); // imprime o vértice
            NoListaAdj* novoNo = novoNoListaAdj(atual->destino); // cria um novo nó para a fila
            if (fila.cabeca == NULL) { // se a fila estiver vazia
                fila.cabeca = novoNo; // define o novo nó como a cabeça da fila
            } else {
                NoListaAdj* ultimo = fila.cabeca; // define o último nó como a cabeça da fila
                while (ultimo->proximo != NULL) {
                    ultimo = ultimo->proximo; // define o próximo nó como o último nó
                }
                ultimo->proximo = novoNo; // define o novo nó como o próximo nó do último nó
            }
        }
        atual = atual->proximo; // define o próximo nó como o nó atual
    }

    while (fila.cabeca != NULL) {
        int vertice_atual = fila.cabeca->destino; // define o vértice atual como o vértice da cabeça da fila
        fila.cabeca = fila.cabeca->proximo; // define o próximo nó como a cabeça da fila
        if (!visitado[vertice_atual]) { // adiciona o vértice apenas se ainda não foi visitado 
            bfs(grafo, vertice_atual); // chama a função bfs recursivamente
            visitado[vertice_atual] = 1; // define o vértice como visitado
        }
    }

    free(visitado);
}

// Imprimir caminho de s até t
void imprimir_caminho_bfs(Grafo* grafo, int s, int t) {
    int* visitado = (int*) malloc(grafo->num_vertices * sizeof(int));
    int* antecessor = (int*) malloc(grafo->num_vertices * sizeof(int));
    for (int i = 0; i < grafo->num_vertices; i++) {
        visitado[i] = 0;
        antecessor[i] = -1; // inicializa o antecessor de todos os vértices como -1 (não visitado)
    }

    ListaAdj fila;
    fila.cabeca = NULL;

    visitado[s] = 1;
    NoListaAdj* atual = grafo->vetor[s].cabeca;
    while (atual != NULL) {
        if (!visitado[atual->destino]) {
            visitado[atual->destino] = 1;
            antecessor[atual->destino] = s;
            NoListaAdj* novoNo = novoNoListaAdj(atual->destino);
            if (fila.cabeca == NULL) {
                fila.cabeca = novoNo;
            } else {
                NoListaAdj* ultimo = fila.cabeca;
                while (ultimo->proximo != NULL) {
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = novoNo;
            }
        }
        atual = atual->proximo;
    }

    while (fila.cabeca != NULL) {
        int vertice_atual = fila.cabeca->destino;
        fila.cabeca = fila.cabeca->proximo;
        if (!visitado[vertice_atual]) {
            visitado[vertice_atual] = 1;
            antecessor[vertice_atual] = s;
            bfs(grafo, vertice_atual);
        }
    }
     if (t >= grafo->num_vertices) { // se o vértice t for igual ou maior que o numero de vertices, t não existe
        printf("O vértice t não existe no grafo.\n");
        return;
    }

    if (antecessor[t] == -1) {
        printf("Nao ha caminho entre os vertices %d e %d\n", s, t);
    } else {
        printf("Caminho entre os vertices %d e %d:\n", s, t);
        int caminho[grafo->num_vertices];
        int i = 0;
        int v = t;
        while (v != s) {
            caminho[i++] = v;
            v = antecessor[v];
        }
        caminho[i++] = s;
        for (int j = i - 1; j >= 0; j--) {
            printf("%d ", caminho[j]);
        }
        printf("\n");
    }

    free(visitado);
    free(antecessor);
}

//Busca em profundidade DFS
void dfs(Grafo* grafo, int vertice, int* visitado) {
    visitado[vertice] = 1; // marca o vértice como visitado
    printf("Visitando vertice %d\n", vertice); // imprime o vértice visitado

    NoListaAdj* atual = grafo->vetor[vertice].cabeca; // define o nó atual como a cabeça da lista de adjacência do vértice

    while (atual != NULL) {
        int vertice_adjacente = atual->destino; // obtém o vértice adjacente
        if (!visitado[vertice_adjacente]) { // verifica se o vértice adjacente ainda não foi visitado
            dfs(grafo, vertice_adjacente, visitado); // chama a função dfs recursivamente para o vértice adjacente
        }
        atual = atual->proximo; // define o próximo nó como o nó atual
    }
}

//Busca em profundidade sem recursão
#define MAX_VERTICES 100

typedef struct {
    int dados[MAX_VERTICES];
    int topo;
} Pilha;

void inicializar_pilha(Pilha* pilha) {
    pilha->topo = -1;
}

void empilhar(Pilha* pilha, int dado) {
    pilha->dados[++pilha->topo] = dado;
}

int desempilhar(Pilha* pilha) {
    return pilha->dados[pilha->topo--];
}

int pilha_vazia(Pilha* pilha) {
    return (pilha->topo == -1);
}

void dfs_iterativo(Grafo* grafo, int vertice, int* visitado) {
    Pilha pilha;
    inicializar_pilha(&pilha);

    empilhar(&pilha, vertice); // adiciona o vértice inicial na pilha

    while (!pilha_vazia(&pilha)) {
        int vertice_atual = desempilhar(&pilha); // retira o último vértice adicionado na pilha

        if (!visitado[vertice_atual]) { // verifica se o vértice ainda não foi visitado
            visitado[vertice_atual] = 1; // marca o vértice como visitado
            printf("Visitando vertice %d\n", vertice_atual); // imprime o vértice visitado

            NoListaAdj* atual = grafo->vetor[vertice_atual].cabeca; // define o nó atual como a cabeça da lista de adjacência do vértice

            while (atual != NULL) {
                int vertice_adjacente = atual->destino; // obtém o vértice adjacente
                if (!visitado[vertice_adjacente]) { // verifica se o vértice adjacente ainda não foi visitado
                    empilhar(&pilha, vertice_adjacente); // adiciona o vértice adjacente na pilha
                }
                atual = atual->proximo; // define o próximo nó como o nó atual
            }
        }
    }
}


int main() {
    char* nome_arquivo_teste = "meu_arquivo_teste.txt"; // nome do arquivo de teste
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo)); // aloca memória para o grafo
    carregarGrafoDeArquivo(grafo, nome_arquivo_teste); // carrega o grafo do arquivo
    imprimirGrafo(grafo); // imprime o grafo
    printf("\n");
    printf("Busca em largura");
    printf("\n");
    bfs(grafo, 1); // chama a função bfs com o vértice inicial 1
    
    printf("\n");
    imprimir_caminho_bfs(grafo,0 , 4); // imprime o caminho entre os vértices 1 e 5
    printf("\n");
    printf("Busca em profundidade");
    printf("\n");
    int* visitado = (int*) malloc(grafo->num_vertices * sizeof(int)); // aloca memória para o vetor de visitados
    for (int i = 0; i < grafo->num_vertices; i++) {
        visitado[i] = 0; // inicializa todos os vértices como não visitados
    }
    dfs(grafo, 0, visitado); // chama a função dfs com o vértice inicial 0
    
    printf("\n");
    printf("Busca em profundidade sem recursão");
    printf("\n");
    int* visitado2 = (int*) malloc(grafo->num_vertices * sizeof(int)); // aloca memória para o vetor de visitados
    for (int i = 0; i < grafo->num_vertices; i++) {
        visitado2[i] = 0; // inicializa todos os vértices como não visitados
    }
    dfs_iterativo(grafo, 0, visitado2); // chama a função dfs com o vértice inicial 0
    
    return 0; 
}