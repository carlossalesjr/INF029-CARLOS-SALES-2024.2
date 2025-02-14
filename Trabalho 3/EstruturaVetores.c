#include <stdio.h>
#include <stdlib.h>
#include "EstruturaVetores.h"

#define TAM 10

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


void inicializar()
{
    int iCont;

    for (iCont = 0; iCont < 10; iCont++)
    {
        vetorPrincipal[iCont] = NULL;
    }

    FILE *Arquivo = fopen("Arq.txt", "r");
    if(Arquivo){
        int tamLinha = 1024;
        char *linha = malloc(sizeof(char) * tamLinha);
        while(fgets(linha, tamLinha, Arquivo) != NULL){
            for(iCont = 0; linha[iCont] != '\n'; ){
                int posicao, tam;
                char *numero = malloc(sizeof(char) * 10);
                if(iCont == 0){
                    adquirirStringNumero(linha, &iCont, numero);
                    posicao = converterStringInt(numero);
                    adquirirStringNumero(linha, &iCont, numero);               
                    tam = converterStringInt(numero);
                    criarEstruturaAuxiliar(posicao, tam);
                }
                adquirirStringNumero(linha, &iCont, numero);               
                inserirNumeroEmEstrutura(posicao, converterStringInt(numero));
            }
        }
        free(linha);
    }
    else{
        Arquivo = fopen("Arq.txt", "w");
    }
    fclose(Arquivo);
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar(){
    int iCont, jCont;
    FILE *Arquivo = fopen("Arq.txt", "w");
    
    for(iCont = 0; iCont < TAM; iCont++){
        if(vetorPrincipal[iCont] != NULL){
            int tamEstrutura = vetorPrincipal[iCont]->topo;
            int vetorAux[tamEstrutura];            
            fprintf(Arquivo, "%d;%d;", iCont + 1, tamEstrutura);
            getDadosEstruturaAuxiliar(iCont + 1, vetorAux);
            
            for(jCont = 0; jCont < tamEstrutura; jCont++){
                fprintf(Arquivo, "%d;",vetorAux[jCont]);
            }
                        
            fprintf(Arquivo,"\n");

            free(vetorPrincipal[iCont]);
            vetorPrincipal[iCont] = NULL;
        }
    }
    fclose(Arquivo);
}

int buscarValorEmVetorAuxiliar(int valor, array estruturaAuxiliar)
{
    int iCont;

    for (iCont = 0; iCont < estruturaAuxiliar.topo; iCont++)
    {
        if (estruturaAuxiliar.valores[iCont] == valor)
        {
            return iCont;
        }
    }

    return -1;
}

int getQtdNumerosTotais(){
    int iCont, tamTotal = 0;

    for (iCont = 0; iCont < TAM; iCont++)
    {
        if (vetorPrincipal[iCont] != NULL)
        {
            tamTotal += vetorPrincipal[iCont]->topo;
        }
    }

    return tamTotal;
} 

int converterStringInt(char *string){
    int iCont = 0, casasNum, base;
    int negativo = 0;
    int num = 0;
    int tam = strlen(string);

    if(string[0] == '-'){
        negativo = 1;
        iCont++;
    }

    casasNum = tam - 1; 
    base = 1;

    while (casasNum > iCont) {
        base *= 10;
        casasNum--;
    }

    while (iCont < tam) { 
        num += (string[iCont] - '0') * base; 
        base /= 10;
        iCont++;
    }

    return negativo ? num * -1 : num;
}

void adquirirStringNumero(char *linha, int *posAtual, char *numero) {
    int jCont = 0;

    while (linha[*posAtual] != ';' && linha[*posAtual] != '\0') {
        numero[jCont] = linha[*posAtual]; 
        (*posAtual)++; 
        jCont++;
    }
    
    numero[jCont] = '\0';
    (*posAtual)++;
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