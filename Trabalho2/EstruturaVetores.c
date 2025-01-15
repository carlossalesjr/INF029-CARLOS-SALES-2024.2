#include <stdio.h>
#include <stdlib.h>
#include "EstruturaVetores.h"

#define TAM 10

typedef struct { 
    int *valores; 
    int tamanho; 
    int topo; 
    } array; 

array *vetorPrincipal[TAM];

int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }
    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }
    if (vetorPrincipal[posicao - 1] != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    vetorPrincipal[posicao - 1] = (array*) malloc(sizeof(array));
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[posicao - 1]->valores = (int*) malloc(tamanho * sizeof(int));
    if (vetorPrincipal[posicao - 1]->valores == NULL) {
        free(vetorPrincipal[posicao - 1]);
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[posicao - 1]->tamanho = tamanho;
    vetorPrincipal[posicao - 1]->topo = 0;
    return SUCESSO;
}

int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (vetorPrincipal[posicao - 1]->topo >= vetorPrincipal[posicao - 1]->tamanho) {
        return SEM_ESPACO;
    }

    vetorPrincipal[posicao - 1]->valores[vetorPrincipal[posicao - 1]->topo] = valor;
    vetorPrincipal[posicao - 1]->topo++;
    return SUCESSO;
}


int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (vetorPrincipal[posicao - 1]->topo == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    vetorPrincipal[posicao - 1]->topo--;
    return SUCESSO;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (vetorPrincipal[posicao - 1]->topo == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    int encontrado = 0;
    for (int i = 0; i < vetorPrincipal[posicao - 1]->topo; i++) {
        if (vetorPrincipal[posicao - 1]->valores[i] == valor) {
            encontrado = 1;
            for (int j = i; j < vetorPrincipal[posicao - 1]->topo - 1; j++) {
                vetorPrincipal[posicao - 1]->valores[j] = vetorPrincipal[posicao - 1]->valores[j + 1];
            }
            vetorPrincipal[posicao - 1]->topo--;
            break;
        }
    }

    if (!encontrado) {
        return NUMERO_INEXISTENTE;
    }

    return SUCESSO;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    for (int i = 0; i < vetorPrincipal[posicao - 1]->topo; i++) {
        vetorAux[i] = vetorPrincipal[posicao - 1]->valores[i];
    }

    return SUCESSO;
}

void insertionSort(int vetor[], int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (retorno == SUCESSO) {
        insertionSort(vetorAux, vetorPrincipal[posicao - 1]->topo);
    }
    return retorno;
}

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int k = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            for (int j = 0; j < vetorPrincipal[i]->topo; j++) {
                vetorAux[k++] = vetorPrincipal[i]->valores[j];
            }
        }
    }
    if (k == 0) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    return SUCESSO;
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
     int retorno = 0;
    int qtdValores = 0;
    retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if(retorno == SUCESSO) {
        for(int i = 0; i < TAM; i++) {
            if(vetorPrincipal[i] != NULL) {
                qtdValores += vetorPrincipal[i]->topo;
            }
        }
        insertion_sort(vetorAux, qtdValores);
    }
    return retorno;
}

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (vetorPrincipal[posicao - 1]->tamanho + novoTamanho < 1) {
        return NOVO_TAMANHO_INVALIDO;
    }

    int *novoArray = (int*) realloc(vetorPrincipal[posicao - 1]->valores, (vetorPrincipal[posicao - 1]->tamanho + novoTamanho) * sizeof(int));
    if (novoArray == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[posicao - 1]->valores = novoArray;
    vetorPrincipal[posicao - 1]->tamanho += novoTamanho;
    return SUCESSO;
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }
    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    return vetorPrincipal[posicao - 1]->topo;
}

No *montarListaEncadeadaComCabecote() {
    No *head = malloc(sizeof(No));
    head->prox = NULL;

    No *last = head;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            for (int j = 0; j < vetorPrincipal[i]->topo; j++) {
                No *new = malloc(sizeof(No));
                new->conteudo = vetorPrincipal[i]->valores[j];
                new->prox = NULL;

                last->prox = new;
                last = new;
            }
        }
    }

    return head;
}


void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    No *atual = inicio->prox;
    int i = 0;
    while (atual != NULL) {
        vetorAux[i] = atual->conteudo;
        atual = atual->prox;
        i++;
    }
}


void destruirListaEncadeadaComCabecote(No **inicio) {
    No *atual = *inicio;
    No *temp;

    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }

    *inicio = NULL;
}


void inicializar() {
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i] = NULL;
    }
}


void finalizar() {
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            free(vetorPrincipal[i]->valores);
            free(vetorPrincipal[i]);
        }
    }
}


void insertion_sort(int *vetorAux, int size) {
    for (int j = 1; j < size; j++) {
        int key = vetorAux[j];
        int i = j - 1;
        while (i >= 0 && vetorAux[i] > key) {
            vetorAux[i + 1] = vetorAux[i];
            i--;
        }
        vetorAux[i + 1] = key;
    }
}

void copyIntArray(int *arrayP, int *arrayS, int size) {
    for (int i = 0; i < size; i++) {
        arrayS[i] = arrayP[i];
    }
}
