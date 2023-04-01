#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // tamanho máximo da lista

typedef struct {
    int data[MAX_SIZE];
    int tamanho;
} Lista;

// cria uma lista vazia
void criar_lista(Lista *lista) {
    lista->tamanho = 0; // inicializa o tamanho com 0 para indicar listaa vazia
}

// verifica se a lista está vazia
int listaEstaVazia(Lista *lista) { 
    return lista->tamanho == 0; // retorna 1 se a lista estiver vazia e 0 caso contrário
}

// retorna o tamanho da lista
int tamanhoLista(Lista *lista) { 
    return lista->tamanho; // retorna o tamanho da lista
}

// obtém o valor em determinada posição
int obterValor(Lista *lista, int pos) {
    if (pos >= 0 && pos < lista->tamanho) { // verifica se a posição é válida
        return lista->data[pos]; // retorna o valor na posição
    } else {
        printf("Posição inválida\n");
        exit(EXIT_FAILURE);
    }
}

// modifica o valor em determinada posição
void modificar_valor(Lista *lista, int pos, int value) {
    if (pos >= 0 && pos < lista->tamanho) { // verifica se a posição é válida
        lista->data[pos] = value; // modifica o valor na posição
    } else {
        printf("Posição inválida\n");
        exit(EXIT_FAILURE);
    }
}

// insere um elemento em determinada posição
void inserirElemento(Lista *lista, int pos, int value) {
    if (lista->tamanho < MAX_SIZE && pos >= 0 && pos <= lista->tamanho) { // verifica se a lista está cheia e se a posição é válida
        for (int i = lista->tamanho; i > pos; i--) { 
            lista->data[i] = lista->data[i-1]; // desloca o elemento para a direita
        }
        lista->data[pos] = value; // insere o elemento na posição
        lista->tamanho++; // incrementa o tamanho da lista
    } else {
        printf("Não é possível inserir na posição %d\n", pos);
        exit(EXIT_FAILURE);
    }
}

// remove um elemento em determinada posição
void retirarElemento(Lista *lista, int pos) {
    if (pos >= 0 && pos < lista->tamanho) { // verifica se a posição é válida
        for (int i = pos; i < lista->tamanho-1; i++) { 
            lista->data[i] = lista->data[i+1]; // desloca o elemento para a esquerda
        }
        lista->tamanho--; // decrementa o tamanho da lista
    } else {
        printf("Posição inválida\n");
        exit(EXIT_FAILURE);
    }
}

// imprime a lista
void imprimirLista(Lista *lista) {
    printf("[ ");
    for (int i = 0; i < lista->tamanho; i++) { 
        printf("%d ", lista->data[i]);
    }
    printf("]\n");
}

int main() {
    Lista lista;
    criar_lista(&lista);

    
    printf("Lista vazia? %s\n", listaEstaVazia(&lista) ? "Sim" : "Nao");
    printf("Tamanho da lista: %d\n", tamanhoLista(&lista));

    inserirElemento(&lista, 0, 10);
    inserirElemento(&lista, 1, 20);
    inserirElemento(&lista, 2, 30);
    imprimirLista(&lista);
    
    printf("\n");
    
    modificar_valor(&lista, 1, 25);
    imprimirLista(&lista);

    printf("\nTamanho da lista: %d\n", tamanhoLista(&lista));
    retirarElemento(&lista, 0);
    imprimirLista(&lista);

    return 0;
}