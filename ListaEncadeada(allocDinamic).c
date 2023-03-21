#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int conteudo; // conteúdo do nó
    struct no *proximo; // ponteiro para o próximo nó
} No; 

typedef struct {
    No *cabeca;  // ponteiro para o primeiro nó da lista
    int tamanho; // tamanho da lista
} ListaEncadeada;

ListaEncadeada *criar_lista() {
    ListaEncadeada *nova_lista = (ListaEncadeada *) malloc(sizeof(ListaEncadeada));
    nova_lista->tamanho = 0;
    nova_lista->cabeca = NULL;
    return nova_lista;
}

int listaEstaVazia(ListaEncadeada *lista) { 
    return lista->tamanho == 0; // retorna 1 se a lista estiver vazia e 0 se não estiver
}

int tamanhoLista(ListaEncadeada *lista) {
    return lista->tamanho; // retorna o tamanho da lista
}

int obterValor(ListaEncadeada *lista, int posicao, int novoValor) {
    if (posicao < 0 || posicao >= lista->tamanho) { //se a posição for menor que 0 ou maior que o tamanho da lista
        printf("Posição inválida!\n");
        return -1;
    }
    
    No *atual = lista->cabeca; // No atual recebe o primeiro nó da lista
    int i;
    
    for (i = 0; i < posicao; i++) { // enquanto i for menor que a posição
        atual = atual->proximo; // atual recebe o próximo nó
    }
    
    return atual->conteudo;
}
void modificar_valor(ListaEncadeada *lista, int posicao, int novoValor) {
    if (posicao < 0 || posicao >= lista->tamanho) { //se a posição for menor que 0 ou maior que o tamanho da lista
        printf("Posição inválida!\n");
        return;
    }
    
    No *atual = lista->cabeca; // No atual recebe o primeiro nó da lista
    int i;
    
    for (i = 0; i < posicao; i++) { // enquanto i for menor que a posição
        atual = atual->proximo; // atual recebe o próximo nó
    }
    
    atual->conteudo = novoValor; // o conteudo do nó atual recebe o novo valor
}

void inserirElemento(ListaEncadeada *lista, int posicao, int valor) {
    if (posicao < 0 || posicao > lista->tamanho) { //se a posição for menor que 0 ou maior que o tamanho da lista
       
        printf("Posição inválida!\n");
        return;
    }
    
    No *novo_no = (No *) malloc(sizeof(No)); // aloca memória para o novo nó
    novo_no->conteudo = valor; // conteudo do novo nó recebe o valor
    
    if (posicao == 0) { // se a posição for igual a 0
        novo_no->proximo = lista->cabeca; // o proximo nó do novo nó recebe o primeiro nó da lista
        lista->cabeca = novo_no; // o primeiro nó da lista recebe o novo nó
    } else {
        No *anterior = lista->cabeca; // No anterior recebe o primeiro nó da lista
        int i;
        
        for (i = 0; i < posicao - 1; i++) { // enquanto i for menor que a posição - 1
            anterior = anterior->proximo; // anterior recebe o próximo nó
        }
        
        novo_no->proximo = anterior->proximo; // o proximo nó do novo nó recebe o proximo nó do anterior
        anterior->proximo = novo_no; // o proximo nó do anterior recebe o novo nó
    }
    
    lista->tamanho++; 
}

void retirarElemento(ListaEncadeada *lista, int posicao) {
    if (listaEstaVazia(lista) || posicao < 0 || posicao > lista->tamanho - 1) {
        printf("Posição inválida!\n");
        return;
    }
    
    No *remover;
     
    if (posicao == 0) {
        remover = lista->cabeca;
        lista->cabeca = lista->cabeca->proximo;
    } else {
        No *anterior = lista->cabeca;
        int i;
        for (i = 0; i < posicao - 1; i++) {
            anterior = anterior->proximo;
        }
        remover = anterior->proximo;
        anterior->proximo = remover->proximo;
    }
    
    free(remover);
    lista->tamanho--;
}


void imprimirLista(ListaEncadeada *lista) {
    if (listaEstaVazia(lista)) {
        printf("Lista vazia!\n");
        return;
    }
    
    No *atual = lista->cabeca;
    
    while (atual != NULL) {
        printf("%d ", atual->conteudo);
        atual = atual->proximo;
    }
}

int main() {
    ListaEncadeada *lista = criar_lista();

    printf("Lista vazia? %d\n" , listaEstaVazia(lista));
    printf("Tamanho da lista: %d\n", tamanhoLista(lista));

    inserirElemento(lista, 0, 10);
    inserirElemento(lista, 1, 20);
    inserirElemento(lista, 2, 30);
    imprimirLista(lista);
    
    printf("\n");
    
    modificar_valor(lista, 1, 25);
    imprimirLista(lista);

    printf("\nTamanho da lista: %d\n", tamanhoLista(lista));
    retirarElemento(lista, 0);
    imprimirLista(lista);

    return 0;
}