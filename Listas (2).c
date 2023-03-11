#include <stdio.h> // necessário para a função printf
#include <stdbool.h> // necessário para o tipo bool
#include <stdlib.h> // necessário para a função malloc
#define MAX 10
// definição da estrutura da lista
typedef struct { 
    int tamanho; // tamanho da lista
    int lista[MAX]; // vetor para armazenar os elementos da lista
} Lista;

// função para criar uma lista vazia
Lista* criarLista() {
    Lista* lista = (Lista*) malloc(sizeof(Lista)); // aloca memória para a lista
    lista->tamanho = 0; // define o tamanho da lista como 0
    return lista; // retorna a lista criada
}

// função para verificar se a lista está vazia
bool listaVazia(Lista* lista) {
    return lista->tamanho == 0; // retorna true se o tamanho da lista for 0
}

// função para verificar se a lista está cheia
bool listaCheia(Lista* lista) {
    return lista->tamanho == MAX; // retorna true se o tamanho da lista for igual ao tamanho máximo
}

// função para obter o tamanho da lista
int tamanhoLista(Lista* lista) {
    return lista->tamanho; // retorna o tamanho da lista
}

// função para obter um elemento da lista
int obterElemento(Lista* lista, int posicao) {
    return lista->lista[posicao]; // retorna o elemento da lista na posição especificada
}

// função para modificar um elemento na lista
void modificarElemento(Lista* lista, int posicao, int elemento) {
    lista->lista[posicao] = elemento; // modifica o elemento na posição especificada
}

// função para inserir um elemento na lista
void inserirElemento(Lista* lista, int posicao, int elemento) {
    if (listaCheia(lista)) { // verifica se a lista está cheia
        printf("Lista cheia!\n"); // imprime mensagem de erro
    } else { // se a lista não estiver cheia
        int i = lista->tamanho; // define o índice inicial como o tamanho da lista
        while (i > posicao) { // percorre a lista a partir do último elemento até a posição especificada
            lista->lista[i] = lista->lista[i-1]; // desloca os elementos para a direita
            i--;
        }
        lista->lista[posicao] = elemento; // insere o elemento na posição especificada
        lista->tamanho++; // incrementa o tamanho da lista
    }
}

// função para retirar um elemento da lista
void retirarElemento(Lista* lista, int posicao) {
    if (listaVazia(lista)) { // verifica se a lista está vazia
        printf("Lista vazia!\n"); // imprime mensagem de erro
    } else { // se a lista não estiver vazia
        int i = posicao; // define o índice inicial como a posição especificada
        while (i < lista->tamanho-1) { // percorre a lista a partir da posição especificada até o penúltimo elemento
            lista->lista[i] = lista->lista[i+1]; // desloca os elementos para a esquerda
            i++;
        }
        lista->tamanho--; // decrementa o tamanho da lista
    }
}

// função principal para testar as operações da lista
int main() {
    Lista* lista = criarLista(); // cria uma lista vazia
    inserirElemento(lista, 0, 1); // insere o elemento 1 na posição 0
    inserirElemento(lista, 1, 2); // insere o elemento 2 na posição 1
    inserirElemento(lista, 2, 3); // insere o elemento 3 na posição 2
    inserirElemento(lista, 3, 4); // insere o elemento 4 na posição 3
    inserirElemento(lista, 4, 5); // insere o elemento 5 na posição 4
    inserirElemento(lista, 5, 6); // insere o elemento 6 na posição 5
    inserirElemento(lista, 6, 7); // insere o elemento 7 na posição 6
    inserirElemento(lista, 7, 8); // insere o elemento 8 na posição 7
    inserirElemento(lista, 8, 9); // insere o elemento 9 na posição 8
    inserirElemento(lista, 9, 10); // insere o elemento 10 na posição 9
    inserirElemento(lista, 10, 11); // insere o elemento 11 na posição 10

    printf("Elemento da posição 5: %d \n", obterElemento(lista, 5)); // imprime o elemento da posição 5

    retirarElemento(lista, 5); // retira o elemento da posição 5

    printf("Elemento da posição 5: %d \n", obterElemento(lista, 5)); // imprime o elemento da posição 5

    modificarElemento(lista, 5, 12); // modifica o elemento da posição 5 para 12

    printf("Tamanho da lista: %d \n", tamanhoLista(lista)); // imprime o tamanho da lista
    printf("Elemento da posição 5: %d \n", obterElemento(lista, 5)); // imprime o elemento da posição 5

    return 0;
}

