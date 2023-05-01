// Matriz de adjacência
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int matriz_adjacencia[MAX_VERTICES][MAX_VERTICES];
    int num_vertices; // número de vértices do grafo
} Grafo;

void inicializar_grafo(Grafo* grafo, int num_vertices) {
    grafo->num_vertices = num_vertices; // atribui o número de vértices do grafo

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            grafo->matriz_adjacencia[i][j] = 0; // inicializa a matriz de adjacência com 0
        }
    }
}

void adicionar_aresta(Grafo* grafo, int v1, int v2) {
    grafo->matriz_adjacencia[v1][v2] = 1; // adiciona a aresta v1 -> v2
    grafo->matriz_adjacencia[v2][v1] = 1; // adiciona a aresta v2 -> v1
}

void carregar_grafo_arquivo(Grafo* grafo, char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r"); // abre o arquivo para leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo); // imprime uma mensagem de erro caso não consiga abrir o arquivo
        return;
    }

    int num_vertices; // número de vértices do grafo
    fscanf(arquivo, "%d\n", &num_vertices); // lê o número de vértices do grafo
    inicializar_grafo(grafo, num_vertices); // inicializa o grafo com o número de vértices lido

    int v1, v2;
    while (fscanf(arquivo, "%d %d\n", &v1, &v2) == 2) { // lê as arestas do grafo
        adicionar_aresta(grafo, v1, v2); // adiciona a aresta v1 -> v2
    }

    fclose(arquivo);
}

void imprimir_matriz_adjacencia(Grafo* grafo) {
    printf("Matriz de adjacência:\n");
    for (int i = 0; i < grafo->num_vertices; i++) { // percorre as linhas da matriz
        for (int j = 0; j < grafo->num_vertices; j++) {
            printf("%d ", grafo->matriz_adjacencia[i][j]); // imprime o valor da posição i, j da matriz
        }
        printf("\n");
    }
}
// Busca em largura (BFS)
void bfs(Grafo* grafo, int inicio) {
    int visitados[MAX_VERTICES] = {0}; // vetor de visitados
    int fila[MAX_VERTICES] = {0}; // fila de vértices a serem visitados
    int frente = 0, tras = 0; // índices da frente e da traseira da fila
    
    visitados[inicio] = 1; // marca
    
    fila[tras++] = inicio; // insere o vértice inicial na fila

    while (frente != tras) { // enquanto a fila não estiver vazia
        int v = fila[frente++]; // retira o vértice da frente da fila

        printf("%d ", v); // imprime o vértice visitado

        for (int i = 0; i < grafo->num_vertices; i++) { // percorre os vértices adjacentes ao vértice atual
            if (grafo->matriz_adjacencia[v][i] == 1 && !visitados[i]) { // se o vértice i é adjacente a v e não foi visitado
                visitados[i] = 1; // marca o vértice como visitado
                fila[tras++] = i; // insere o vértice na fila
            }
        }
    }
}

//imprime o caminho entre dois vértices s e t
void imprimir_caminho(Grafo* grafo, int s, int t) {
    int visitados[MAX_VERTICES] = {0}; // vetor de visitados
    int fila[MAX_VERTICES] = {0}; // fila de vértices a serem visitados
    int predecessores[MAX_VERTICES] = {-1}; // vetor de predecessores
    int frente = 0, tras = 0; // índices da frente e da traseira da fila
    
    visitados[s] = 1; // marca
    fila[tras++] = s; // insere o vértice inicial na fila

    while (frente != tras) { // enquanto a fila não estiver vazia
        int atual = fila[frente++]; // retira o vértice da frente da fila
        for (int i = 0; i < grafo->num_vertices; i++) { // percorre os vértices adjacentes ao vértice atual
            if (grafo->matriz_adjacencia[atual][i] && !visitados[i]) { // se o vértice i é adjacente a atual e não foi visitado
                visitados[i] = 1; // marca o vértice como visitado
                predecessores[i] = atual; // define o predecessor do vértice i como o vértice atual
                fila[tras++] = i; // insere o vértice na fila
            }
        }
    }
    
    if (t >= grafo->num_vertices) { // se o vértice t for igual ou maior que o numero de vertices, t não existe
        printf("O vértice t não existe no grafo.\n");
        return;
    }

    if (predecessores[t] != t-1) { // se não há conexão entre t (ultimo vertice) e seu antecessor então não há caminho
        printf("Não há caminho entre os vértices.\n");
        return;
    }

    printf("Caminho entre os vértices %d e %d: ", s, t);
    int caminho[MAX_VERTICES], indice = 0; // vetor que armazena o caminho e índice do vetor
    caminho[indice++] = t; // insere o vértice t no caminho
    while (predecessores[t] != -1) { // enquanto não chegar no vértice s
        caminho[indice++] = predecessores[t]; // insere o antecessor de t no caminho
        t = predecessores[t]; // atualiza o valor de t para seu antecessor
    }
    for (int i = indice - 1; i >= 0; i--) {
        printf("%d ", caminho[i]);
    }
    printf("\n");
}

// Busca em profundidade (DFS)
void dfs(Grafo* grafo, int v, int* visitados) {
    visitados[v] = 1; // marca o vértice como visitado
    printf("%d ", v); // imprime o vértice visitado

    for (int i = 0; i < grafo->num_vertices; i++) { // percorre os vértices adjacentes ao vértice atual
        if (grafo->matriz_adjacencia[v][i] == 1 && !visitados[i]) { // se o vértice i é adjacente a v e não foi visitado
            dfs(grafo, i, visitados); // visita o vértice i recursivamente
        }
    }
}

// Busca em profundidade DFS sem recursão
void dfs_iterativo(Grafo* grafo, int inicio) {
    int visitados[MAX_VERTICES] = {0}; // vetor de visitados
    int pilha[MAX_VERTICES], topo = 0; // pilha para guardar os vértices a serem visitados
    pilha[topo++] = inicio; // empilha o vértice inicial

    while (topo > 0) { // enquanto houver vértices na pilha
        int v = pilha[--topo]; // desempilha o último vértice adicionado

        if (!visitados[v]) { // se o vértice ainda não foi visitado
            visitados[v] = 1; // marca o vértice como visitado
            printf("%d ", v); // imprime o vértice visitado

            for (int i = grafo->num_vertices - 1; i >= 0; i--) { // percorre os vértices adjacentes ao vértice atual
                if (grafo->matriz_adjacencia[v][i] == 1 && !visitados[i]) { // se o vértice i é adjacente a v e não foi visitado
                    pilha[topo++] = i; // empilha o vértice i para visitar posteriormente
                }
            }
        }
    }
}
// Arquivo de teste
// 6
// 0 1
// 0 2
// 1 2
// 2 3
// 4 5
int main() {
    char* nome_arquivo_teste = "meu_arquivo_teste.txt"; // nome do arquivo de teste

    Grafo grafo; // cria um grafo
    carregar_grafo_arquivo(&grafo, nome_arquivo_teste); // carrega o grafo a partir do arquivo
    imprimir_matriz_adjacencia(&grafo); // imprime a matriz de adjacência do grafo
    
    printf("\n");
    printf("Busca em largura (BFS): ");
    bfs(&grafo, 0); // busca em largura a partir do vértice 0
    printf("\n");

    int s = 0, t = 5; // vértices inicial e final do caminho
    printf("imprime o caminho entre %d e %d usando BFS: ", s,t);
    imprimir_caminho(&grafo, s, t); // imprime o caminho entre os vértices s e t
    

    printf("\nBusca em profundidade (DFS): ");
    int visitados[MAX_VERTICES] = {0}; // vetor de visitados
    dfs(&grafo, 0, visitados); // busca em profundidade a partir do vértice 0
    
    printf("\nBusca em profundidade (DFS) sem recursão: ");
    dfs_iterativo(&grafo, 0); // busca em profundidade sem recursão a partir do vértice 0

    remove(nome_arquivo_teste); // remove o arquivo de teste
    return 0;
}