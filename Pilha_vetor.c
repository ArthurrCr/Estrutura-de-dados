#include <stdio.h>
#include <stdlib.h>

#define MAX 10 // tamanho máximo da pilha

int pilha[MAX];
int topo = -1; // inicializa o topo com -1 para indicar pilha vazia

void push(int valor) {
    if (topo == MAX-1) { // verifica se a pilha está cheia
        printf("Pilha cheia\n");
        return;
    }
    topo++; // incrementa o topo
    pilha[topo] = valor; // insere o valor no topo
}

void pop() {
    if (topo == -1) { // verifica se a pilha está vazia
        printf("Pilha vazia\n");
        return;
    }
    topo--; // decrementa o topo
}

int ler_topo() {
    if (topo == -1) { // verifica se a pilha está vazia
        printf("Pilha vazia\n");
        return -1;
    }
    return pilha[topo]; // retorna o valor do topo
}

int pilha_vazia() {
    return topo == -1; // retorna 1 se a pilha estiver vazia e 0 caso contrário
}

int tamanho_pilha() {
    return topo + 1; // retorna o tamanho da pilha
}

int main() {
    push(1);
    push(2);
    push(3);
    printf("Topo: %d\n", ler_topo());
    pop();
    printf("Topo: %d\n", ler_topo());
    printf("Tamanho da pilha: %d\n", tamanho_pilha());
    printf("Pilha vazia? %s\n", pilha_vazia() ? "Sim" : "Nao");
    return 0;
}