#include "gerador.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 10000
#define NUMERO_BALDES 300

// FUNÇÕES COMPLEMENTARES

void backupArr(int* arr, int* buffArr){
    for(int i = 0; i<TAMANHO; i++){
        buffArr[i] = arr[i];
    }
}


int mediana(int a, int b, int c) {
    if ((a > b && a < c) || (a < b && a > c)) {
        return a;
    } else if ((b > a && b < c) || (b < a && b > c)) {
        return b;
    } else {
        return c;
    }
}

typedef struct {
    int *balde;
    int topo;
} Balde;


// ALGORITMO BOLHA
void bolha(int *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                int aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
            }
        }
    }
}

// ALGORITMO BOLHA COM PARADA
void bolhaParada(int* arr, int n){
    int mudou = 1;
    int indice = n-1;
    while(mudou){
        int j = 1;
        mudou = 0;
        while(j<n){
            if(arr[j-1]> arr[j]){
                int aux = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = aux;
                mudou = 1;
            }
            indice = j;
            j++;
        }
        n = indice;
    }
}


// INSERÇÃO DIRETA
void insercaoDireta(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int auxiliar = arr[i];
        int j = i - 1;

        while (j >= 0 && auxiliar < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }

        if (j != i - 1) {
            arr[j + 1] = auxiliar;
        }
    }
}


// INSERÇÃO BINARIA
void insercaoBinaria(int* arr, int n){
    for(int i = 1; i<n; i++){
        int aux = arr[i];
        int esq = 0;
        int dir = i;
        while(esq<dir){
            int meio = (esq+dir)/2;
            if(arr[meio]<=aux){
                esq = meio+1;
            }else{
                dir = meio;
            }
        }
        for(int j = i; j>esq; j--){
            arr[j] = arr[j-1];
        }
        arr[dir] = aux;
    }
}


// SHELL SORT
void shellsort(int *arr, int n) {
    int h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < n; i++) {
            int auxiliar = arr[i];
            int j = i;
            while (j >= h && arr[j - h] > auxiliar) {
                arr[j] = arr[j - h];
                j -= h;
            }
            arr[j] = auxiliar;
        }
        h = h / 3;
    }
}



// SELEÇÃO DIRETA
void selecaoDireta(int* arr, int n){
    for(int i = 0; i<n-1; i++){
        int menor = i;
        for(int j = i+1; j<n; j++){
            if(arr[j]<arr[menor]){
                menor = j;
            }
        }
        if(i!=menor){
            int aux = arr[i];
            arr[i] = arr[menor];
            arr[menor] = aux;
        }
        
    }
}



// HEAP SORT
void criaHeap(int *arr, int inicio, int final) {
    int auxiliar = arr[inicio];
    int j = 2 * inicio + 1;

    while (j <= final) {
        if (j < final && arr[j] < arr[j + 1]) {
            j = j + 1;
        }
        if (auxiliar < arr[j]) {
            arr[inicio] = arr[j];
            inicio = j;
            j = 2 * inicio + 1;
        } else {
            j = final + 1;
        }
    }
    arr[inicio] = auxiliar;
}

void heapsort(int *arr, int n) {
    for (int i = (n - 1) / 2; i >= 0; i--) {
        criaHeap(arr, i, n - 1);
    }

    for (int i = n - 1; i > 0; i--) {
        int auxiliar = arr[0];
        arr[0] = arr[i];
        arr[i] = auxiliar;
        criaHeap(arr, 0, i - 1);
    }
}



// QUICKSORT COM PIVÔ NO INICIO
int particaoQSIni(int esq, int dir, int* arr) {
    int i = esq;
    int j = dir;
    int pivo = arr[esq];

    while (i <= j) {
        while (i <= j && arr[i] < pivo) i++;
        while (i <= j && arr[j] > pivo) j--;
        if (i <= j) {
            int aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
            i++;
            j--;
        }
    }
    return i - 1;
}

void quickSortIni(int* arr, int esq, int dir) {
    if (esq < dir) {
        int j = particaoQSIni(esq, dir, arr);
        if (j > esq) quickSortIni(arr, esq, j);
        if (j + 1 <= dir) quickSortIni(arr, j + 1, dir);
    }
}


// QUICKSORT COM PIVÔ NO MEIO
int particaoQSMeio(int esq, int dir, int* arr) {
    int i = esq;
    int j = dir;
    int pivo = arr[(esq+dir)/2];

    while (i <= j) {
        while (i <= j && arr[i] < pivo) i++;
        while (i <= j && arr[j] > pivo) j--;
        if (i <= j) {
            int aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
            i++;
            j--;
        }
    }
    return i - 1;
}

void quickSortMeio(int* arr, int esq, int dir) {
    if (esq < dir) {
        int j = particaoQSMeio(esq, dir, arr);
        if (j > esq) quickSortMeio(arr, esq, j);
        if (j + 1 <= dir) quickSortMeio(arr, j + 1, dir);
    }
}


// QUICKSORT COM PIVÔ NA MEDIANA
int particaoQSMediana(int esq, int dir, int* arr) {
    int i = esq;
    int j = dir;
    int pivo = mediana(arr[esq], arr[(esq + dir) / 2], arr[dir]);
    while (i <= j) {
        while (i <= j && arr[i] < pivo) i++;
        while (i <= j && arr[j] > pivo) j--;
        if (i <= j) {
            int aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
            i++;
            j--;
        }
    }
    int aux = arr[i];
    arr[i] = pivo;
    arr[dir] = aux;

    return i-1;
}

void quickSortMediana(int* arr, int esq, int dir) {
    if (esq < dir) {
        int j = particaoQSMediana(esq, dir, arr);
        quickSortMediana(arr, esq, j - 1); 
        quickSortMediana(arr, j + 1, dir);
    }
}


// MERGE SORT
void intercalar(int *arr, int inicio, int meio, int fim) {
    int *tmp = malloc((fim - inicio + 1) * sizeof(int));
    int i = inicio;
    int j = meio + 1;
    int k = 0;

    while (i <= meio && j <= fim) {
        if (arr[i] <= arr[j]) {
            tmp[k] = arr[i];
            i++;
        } else {
            tmp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= meio) {
        tmp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= fim) {
        tmp[k] = arr[j];
        j++;
        k++;
    }

    for (i = inicio, k = 0; i <= fim; i++, k++) {
        arr[i] = tmp[k];
    }

    free(tmp);
}

void mergeSort(int *arr, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(arr, inicio, meio);
        mergeSort(arr, meio + 1, fim);
        intercalar(arr, inicio, meio, fim);
    }
}



// RADIXSORT
int obterDigito(int numero, int posicao) {
    return (numero / posicao) % 10;
}
void countingSortPorDigito(int* arr, int n, int posicao) {
    int* output = (int*)malloc(sizeof(int) * n);
    int* count = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int digito = obterDigito(arr[i], posicao);
        count[digito]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int digito = obterDigito(arr[i], posicao);
        output[count[digito] - 1] = arr[i];
        count[digito]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    free(output);
    free(count);
}

void radixSort(int* arr, int n) {
    int maior = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maior) {
            maior = arr[i];
        }
    }
    for (int posicao = 1; maior / posicao > 0; posicao *= 10) {
        countingSortPorDigito(arr, n, posicao);
    }
}



//BUCKET SORT
void bucketSort(int *arr, int tamanho) {
    Balde baldes[NUMERO_BALDES];
    for (int i = 0; i < NUMERO_BALDES; i++) {
        baldes[i].balde = malloc(tamanho * sizeof(int));
        baldes[i].topo = 0;
    }

    for (int i = 0; i < tamanho; i++) {
        int j = NUMERO_BALDES - 1;
        while (j >= 0) {
            if (arr[i] >= j * 10) {
                baldes[j].balde[baldes[j].topo] = arr[i];
                baldes[j].topo++;
                break;
            }
            j--;
        }
    }

    for (int i = 0; i < NUMERO_BALDES; i++) {
        if (baldes[i].topo > 0) {
            bolha(baldes[i].balde, baldes[i].topo);
        }
    }

    int index = 0;
    for (int j = 0; j < NUMERO_BALDES; j++) {
        for (int k = 0; k < baldes[j].topo; k++) {
            arr[index] = baldes[j].balde[k];
            index++;
        }
        free(baldes[j].balde);
    }
}


int main() {
    int arr[TAMANHO];
    int buffArr[TAMANHO];
    clock_t inicio, fim;
    double tempo_gasto;
    srand(time(NULL));
    
    //gerar_aleatorio(arr, TAMANHO);
    
    //gerar_crescente(arr, TAMANHO);
    
    gerar_decrescente(arr, TAMANHO);
    
    backupArr(arr, buffArr);

    inicio = clock();
    bolha(arr, TAMANHO);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao BOLHA:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);


    inicio = clock();
    bolhaParada(arr, TAMANHO);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao BOLHA COM PARADA:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);


    inicio = clock();
    insercaoDireta(arr, TAMANHO);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao INSERCAO DIRETA:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);


    inicio = clock();
    insercaoBinaria(arr, TAMANHO);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao INSERCAO BINARIA:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);


    inicio = clock();
    shellsort(arr, TAMANHO);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao SHELLSORT:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);


    inicio = clock();
    selecaoDireta(arr, TAMANHO);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao SELECAO DIRETA:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr); 


    inicio = clock();
    heapsort(arr, TAMANHO);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao HEAPSORT:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);


    inicio = clock();
    quickSortIni(arr, 0, TAMANHO - 1);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao QUICKSORT INICIO:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);


    inicio = clock();
    quickSortMeio(arr, 0, TAMANHO - 1);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao QUICKSORT MEIO:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);


    inicio = clock();
    quickSortMediana(arr, 0, TAMANHO - 1);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao QUICKSORT MEDIANA:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);


    inicio = clock();
    mergeSort(arr, 0, TAMANHO - 1);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao MERGESORT:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);
    

    inicio = clock();
    radixSort(arr, TAMANHO);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao RADIXSORT:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);


    inicio = clock();
    bucketSort(arr, TAMANHO);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao BUCKETSORT:\t %f segundos\n", tempo_gasto);
    backupArr(buffArr, arr);
        
    
    return 0;
}
