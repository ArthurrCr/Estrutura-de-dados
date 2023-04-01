#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no* proximo;
} No;

No* topo = NULL; // inicializa o topo como NULL para indicar pilha vazia

void push(int valor) {
    No* novo_no = (No*) malloc(sizeof(No)); // aloca memória para o novo nó
    novo_no->valor = valor; // atribui o valor ao novo nó
    novo_no->proximo = topo; // o próximo do novo nó aponta para o topo
    topo = novo_no; // o topo aponta para o novo nó
}

void pop() {
    if (topo == NULL) { // se o topo for NULL, a pilha está vazia
        printf("Pilha vazia\n");
        return;
    }
    No* no_removido = topo; // o nó removido recebe o topo
    topo = topo->proximo; // o topo recebe o próximo do topo
    free(no_removido); // libera a memória do nó removido
}

int ler_topo() {
    if (topo == NULL) { // se o topo for NULL, a pilha está vazia
        printf("Pilha vazia\n");
        return -1;
    }
    return topo->valor; // retorna o valor do topo
}

int pilha_vazia() {
    return topo == NULL; // retorna 1 se o topo for NULL, 0 caso contrário
}

int tamanho_pilha() {
    int tamanho = 0; // inicializa o tamanho da pilha como 0
    No* no_atual = topo; // o nó atual recebe o topo
    while (no_atual != NULL) { // enquanto o nó atual for diferente de NULL
        tamanho++; // incrementa o tamanho da pilha
        no_atual = no_atual->proximo; // o nó atual recebe o próximo do nó atual
    }
    return tamanho; // retorna o tamanho da pilha
}

int main() {
    push(1); // insere o valor 1 no topo da pilha
    push(2); // insere o valor 2 no topo da pilha
    push(3); // insere o valor 3 no topo da pilha
    printf("Topo: %d\n", ler_topo()); // imprime o valor do topo da pilha
    pop(); // remove o valor do topo da pilha
    printf("Topo: %d\n", ler_topo()); // imprime o valor do topo da pilha
    printf("Tamanho da pilha: %d\n", tamanho_pilha()); // imprime o tamanho da pilha
    printf("Pilha vazia? %s\n", pilha_vazia() ? "Sim" : "Nao"); // imprime se a pilha está vazia ou não
    return 0;
}