#include "gerador.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 100000
#define NUMERO_BALDES 500

// FUNÇÕES COMPLEMENTARES


void imprimirArray(int* arr){
    for(int i = 0; i<TAMANHO; i++){
        printf("%d ", arr[i]);
    }
}

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

typedef struct {
    int esq, dir;
} Pilha;


// ALGORITMO BOLHA

void bolha(int *arr, int n, long long int *comparacoes, long long int *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            (*comparacoes)++; // Contabiliza a comparação arr[j] > arr[j + 1]
            if (arr[j] > arr[j + 1]) {
                int aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
                (*trocas)++; // Contabiliza a troca
            }
        }
    }
}


// ALGORITMO BOLHA COM PARADA
void bolhaParada(int *arr, int n, long long int *comparacoes, long long int *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    
    int mudou = 1;
    int indice = n - 1;

    while (mudou) {
        int j = 1;
        mudou = 0;

        while (j < n) {
            (*comparacoes)++; // Contabiliza a comparação arr[j-1] > arr[j]
            if (arr[j - 1] > arr[j]) {
                int aux = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = aux;
                mudou = 1;
                (*trocas)++; // Contabiliza a troca
            }
            indice = j;
            j++;
        }
        n = indice;
    }
}


// INSERÇÃO DIRETA
void insercaoDireta(int *arr, int n, long long int *comparacoes, long long int *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 1; i < n; i++) {
        int auxiliar = arr[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++; // Contabiliza a comparação auxiliar < arr[j]
            if (auxiliar < arr[j]) {
                arr[j + 1] = arr[j];
                j--;
                (*trocas)++; // Contabiliza a troca
            } else {
                break;
            }
        }

        if (j + 1 != i) {
            arr[j + 1] = auxiliar;
            (*trocas)++; // Contabiliza a troca final do elemento
        }
    }
}


// INSERÇÃO BINARIA
void insercaoBinaria(int *arr, int n, long long int *comparacoes, long long int *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 1; i < n; i++) {
        int aux = arr[i];
        int esq = 0;
        int dir = i;

        // Busca binária para encontrar a posição correta
        while (esq < dir) {
            (*comparacoes)++;
            int meio = (esq + dir) / 2;
            if (arr[meio] <= aux) {
                esq = meio + 1;
            } else {
                dir = meio;
            }
        }

        // Apenas realiza trocas se a posição de inserção for diferente de i
        if (esq != i) {
            for (int j = i; j > esq; j--) {
                arr[j] = arr[j - 1];
                (*trocas)++;
            }
            arr[esq] = aux;
            (*trocas)++;
        }
    }
}


// SHELL SORT
void shellsort(int *vet, int count, long long int* trocas, long long int* comparacoes){ 
    int i , j , value;
    int gap = 1;
    while(gap < count) {
        gap = 3*gap+1; }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < count; i++) {
            value = vet[i];
            j = i - gap;
            if(j >= 0){
                comparacoes++;
            }
            while (j >= 0 && value < vet[j]) {
                vet [j + gap] = vet[j];
                j -= gap; 
                trocas++;
            }
            vet [j + gap] = value;
        } 
    } 
}



// SELEÇÃO DIRETA
void selecaoDireta(int *arr, int n, long long int *comparacoes, long long int *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++; // Contabiliza a comparação arr[j] < arr[menor]
            if (arr[j] < arr[menor]) {
                menor = j;
            }
        }

        if (i != menor) {
            int aux = arr[i];
            arr[i] = arr[menor];
            arr[menor] = aux;
            (*trocas)++; // Contabiliza a troca
        }
    }
}




void criaHeap(int *arr, int inicio, int final, long long int *comparacoes, long long int *trocas) {
    int auxiliar = arr[inicio];
    int j = 2 * inicio + 1;

    while (j <= final) {
        (*comparacoes)++; // Comparação entre filhos do heap
        if (j < final && arr[j] < arr[j + 1]) {
            j = j + 1;
        }

        (*comparacoes)++; // Comparação entre auxiliar e arr[j]
        if (auxiliar < arr[j]) {
            arr[inicio] = arr[j];
            inicio = j;
            j = 2 * inicio + 1;
            (*trocas)++; // Contabiliza a troca
        } else {
            j = final + 1;
        }
    }
    arr[inicio] = auxiliar;
}

void heapsort(int *arr, int n, long long int *comparacoes, long long int *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    // Construção do heap
    for (int i = (n - 1) / 2; i >= 0; i--) {
        criaHeap(arr, i, n - 1, comparacoes, trocas);
    }

    // Extração dos elementos do heap
    for (int i = n - 1; i > 0; i--) {
        int auxiliar = arr[0];
        arr[0] = arr[i];
        arr[i] = auxiliar;
        (*trocas)++; // Contabiliza a troca entre a raiz e o último elemento

        criaHeap(arr, 0, i - 1, comparacoes, trocas);
    }
}



// QUICKSORT COM PIVÔ NO INICIO
int particaoQSIni(int *arr, int esq, int dir, long long int *comparacoes, long long int *trocas) {
    int pivo = arr[esq];
    int i = esq - 1, j = dir + 1;

    while (1) {
        do {
            i++;
            (*comparacoes)++;  // Comparação 1
        } while (arr[i] < pivo);

        do {
            j--;
            (*comparacoes)++;  // Comparação 2
        } while (arr[j] > pivo);

        if (i >= j) return j;

        int aux = arr[i];
        arr[i] = arr[j];
        arr[j] = aux;
        (*trocas)++;  // Troca 1
    }
}

// Implementação iterativa do QuickSort
void quickSortIterativo(int *arr, int n, long long int *comparacoes, long long int *trocas) {
    Pilha stack[TAMANHO];
    int topo = 0;

    stack[topo++] = (Pilha){0, n - 1};

    while (topo > 0) {
        Pilha atual = stack[--topo];
        int esq = atual.esq, dir = atual.dir;

        if (esq < dir) {
            int j = particaoQSIni(arr, esq, dir, comparacoes, trocas);

            // Empilha os subarrays (o maior sempre por último para otimizar espaço)
            if (j + 1 < dir) stack[topo++] = (Pilha){j + 1, dir};
            if (esq < j) stack[topo++] = (Pilha){esq, j};
        }
    }
}


// QUICKSORT COM PIVÔ NO MEIO
int particaoQSMeio(int esq, int dir, int* arr, long long int *comparacoes, long long int *trocas) {
    int i = esq;
    int j = dir;
    int pivo = arr[(esq + dir) / 2];

    while (i <= j) {
        while (i <= j && arr[i] < pivo) {
            i++;
            (*comparacoes)++;  // Comparação 1
        }
        while (i <= j && arr[j] > pivo) {
            j--;
            (*comparacoes)++;  // Comparação 2
        }
        if (i <= j) {
            int aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
            (*trocas)++;  // Troca 1
            i++;
            j--;
        }
    }
    return i - 1;
}

void quickSortMeio(int* arr, int esq, int dir, long long int *comparacoes, long long int *trocas) {
    if (esq < dir) {
        int j = particaoQSMeio(esq, dir, arr, comparacoes, trocas);
        if (j > esq) quickSortMeio(arr, esq, j, comparacoes, trocas);
        if (j + 1 <= dir) quickSortMeio(arr, j + 1, dir, comparacoes, trocas);
    }
}



// QUICKSORT COM PIVÔ NA MEDIANA
int particaoQSMediana(int esq, int dir, int* arr, long long int* comparacoes, long long int* trocas) {
    int i = esq;
    int j = dir;
    int pivo = mediana(arr[esq], arr[(esq + dir) / 2], arr[dir]);

    while (i <= j) {
        while (i <= j && arr[i] < pivo) {
            i++;
            (*comparacoes)++;  // Comparação 1
        }
        while (i <= j && arr[j] > pivo) {
            j--;
            (*comparacoes)++;  // Comparação 2
        }
        if (i <= j) {
            int aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
            (*trocas)++;  // Troca 1
            i++;
            j--;
        }
    }

    int aux = arr[i];
    arr[i] = pivo;
    arr[dir] = aux;
    (*trocas)++;  // Troca 2

    return i - 1;
}

// Implementação iterativa do QuickSort com Pilha
void quickSortMediana(int* arr, int n, long long int* comparacoes, long long int* trocas) {
    int esq, dir;
    // Criar a pilha para armazenar os intervalos
    int* pilhaEsq = (int*)malloc(n * sizeof(int));
    int* pilhaDir = (int*)malloc(n * sizeof(int));
    int topo = -1;

    // Inicializar a pilha com o intervalo inteiro
    pilhaEsq[++topo] = 0;
    pilhaDir[topo] = n - 1;

    // Enquanto a pilha não estiver vazia
    while (topo >= 0) {
        esq = pilhaEsq[topo];
        dir = pilhaDir[topo--];

        // Realiza a partição e obtém o índice do pivô
        if (esq < dir) {
            int j = particaoQSMediana(esq, dir, arr, comparacoes, trocas);

            // Empilha os subintervalos
            pilhaEsq[++topo] = esq;
            pilhaDir[topo] = j - 1;

            pilhaEsq[++topo] = j + 1;
            pilhaDir[topo] = dir;
        }
    }

    // Liberar a memória da pilha
    free(pilhaEsq);
    free(pilhaDir);
}

// MERGE SORT
void merge(int* arr, int n, long long int *comparacoes, long long int *trocas) {
    int meio, i, j, k;
    int* auxiliar;
    auxiliar = (int*) malloc(n * sizeof(int));
    if (auxiliar == NULL) {
        return;
    }

    meio = n / 2;
    i = 0;
    k = 0;
    j = meio;

    // Intercala os dois subarrays
    while (i < meio && j < n) {
        (*comparacoes)++;  // Conta a comparação arr[i] <= arr[j]
        if (arr[i] <= arr[j]) {
            auxiliar[k++] = arr[i++];
        } else {
            auxiliar[k++] = arr[j++];
        }
        (*trocas)++;  // Conta a atribuição ao array auxiliar
    }

    // Caso restem elementos em um dos subarrays, os adiciona no auxiliar
    if (i == meio) {
        while (j < n) {
            auxiliar[k++] = arr[j++];
            (*trocas)++;  // Conta a atribuição ao array auxiliar
        }
    } else {
        while (i < meio) {
            auxiliar[k++] = arr[i++];
            (*trocas)++;  // Conta a atribuição ao array auxiliar
        }
    }

    // Copia os elementos de volta para o array original
    for (i = 0; i < n; ++i) {
        arr[i] = auxiliar[i];
        (*trocas)++;  // Conta a atribuição ao array original
    }

    free(auxiliar);
}

void mergeSort(int* arr, int n, long long int *comparacoes, long long int *trocas) {
    *comparacoes = 0;  // Inicializa o contador de comparações
    *trocas = 0;       // Inicializa o contador de trocas

    if (n > 1) {
        int meio = n / 2;
        mergeSort(arr, meio, comparacoes, trocas);            // Recursão na primeira metade
        mergeSort(arr + meio, n - meio, comparacoes, trocas); // Recursão na segunda metade
        merge(arr, n, comparacoes, trocas);                   // Intercala os resultados
    }
}

// RADIXSORT
int obterDigito(int numero, int posicao) {
    return (numero / posicao) % 10;
}

void countingSortPorDigito(int* arr, int n, int posicao, long long int* comparacoes, long long int* trocas) {
    int* output = (int*)malloc(sizeof(int) * n);
    int* count = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        count[i] = 0;
    }

    // Contagem dos dígitos
    for (int i = 0; i < n; i++) {
        int digito = obterDigito(arr[i], posicao);
        (*comparacoes)++; // Cada vez que o dígito é obtido
        count[digito]++;
    }

    // Acumulando as contagens
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
        (*comparacoes)++; // Cada vez que fazemos count[i] += count[i - 1]
    }

    // Construção do array ordenado
    for (int i = n - 1; i >= 0; i--) {
        int digito = obterDigito(arr[i], posicao);
        output[count[digito] - 1] = arr[i];
        count[digito]--;
        (*trocas)++; // Cada vez que movemos um valor para output
    }

    // Copiando os dados de volta para o array original
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        (*trocas)++; // Cada vez que copiamos para o array original
    }

    free(output);
    free(count);
}

void radixSort(int* arr, int n, long long int* comparacoes, long long int* trocas) {
    int maior = arr[0];
    *comparacoes = 0; // Inicializando comparações
    *trocas = 0; // Inicializando trocas

    // Encontrando o maior número para determinar o número de dígitos
    for (int i = 1; i < n; i++) {
        (*comparacoes)++; // Conta a comparação arr[i] > maior
        if (arr[i] > maior) {
            maior = arr[i];
        }
    }

    // Ordenando por cada dígito (unidades, dezenas, etc.)
    for (int posicao = 1; maior / posicao > 0; posicao *= 10) {
        countingSortPorDigito(arr, n, posicao, comparacoes, trocas);
    }
}



//BUCKET SORT
void bucketSort(int *arr, int tamanho, long long int *comparacoes, long long int *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    
    Balde baldes[NUMERO_BALDES];
    
    // Inicialização dos baldes
    for (int i = 0; i < NUMERO_BALDES; i++) {
        baldes[i].balde = malloc(tamanho * sizeof(int));
        baldes[i].topo = 0;
    }

    // Distribuindo os elementos para os baldes
    for (int i = 0; i < tamanho; i++) {
        int j = NUMERO_BALDES - 1;
        while (j >= 0) {
            (*comparacoes)++; // Comparação arr[i] >= j * 10
            if (arr[i] >= j * 10) {
                baldes[j].balde[baldes[j].topo] = arr[i];
                baldes[j].topo++;
                (*trocas)++; // Contabiliza a troca de colocação no balde
                break;
            }
            j--;
        }
    }

    // Ordenando os baldes com o método de bolha
    for (int i = 0; i < NUMERO_BALDES; i++) {
        if (baldes[i].topo > 0) {
            bolha(baldes[i].balde, baldes[i].topo, comparacoes, trocas); // Usando a versão modificada do bolha
        }
    }

    // Reunindo os elementos dos baldes de volta no array original
    int index = 0;
    for (int j = 0; j < NUMERO_BALDES; j++) {
        for (int k = 0; k < baldes[j].topo; k++) {
            arr[index] = baldes[j].balde[k];
            index++;
        }
        free(baldes[j].balde); // Liberando a memória dos baldes
    }
}

int main() {
    int arr[TAMANHO];
    int buffArr[TAMANHO];
    long long int comparacoes, trocas;
    clock_t inicio, fim;
    double tempo_gasto;
    srand(time(NULL));
    
    //gerar_aleatorio(arr, TAMANHO);
    
    //gerar_crescente(arr, TAMANHO);
    
    gerar_decrescente(arr, TAMANHO);
    
    backupArr(arr, buffArr);
    

    
    inicio = clock();
    bolha(arr, TAMANHO, &comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao BOLHA:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);


    inicio = clock();
    bolhaParada(arr, TAMANHO, &comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao BOLHA COM PARADA:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);


    inicio = clock();
    insercaoDireta(arr, TAMANHO,&comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao INSERCAO DIRETA:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);


    inicio = clock();
    insercaoBinaria(arr, TAMANHO,&comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao INSERCAO BINARIA:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);


    inicio = clock();
    shellsort(arr, TAMANHO, &comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao SHELLSORT:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);


    inicio = clock();
    selecaoDireta(arr, TAMANHO, &comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao SELECAO DIRETA:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr); 


    inicio = clock();
    heapsort(arr, TAMANHO, &comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao HEAPSORT:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);

    
    inicio = clock();
    quickSortIterativo(arr,  TAMANHO, &comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao QUICKSORT INICIO:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);
    
    


    inicio = clock();
    quickSortMeio(arr, 0, TAMANHO - 1, &comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao QUICKSORT MEIO:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);


    inicio = clock();
    quickSortMediana(arr, TAMANHO, &comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao QUICKSORT MEDIANA:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);
 

    inicio = clock();
    mergeSort(arr, TAMANHO - 1, &comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao MERGESORT:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);
    

    inicio = clock();
    radixSort(arr, TAMANHO, &comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao RADIXSORT:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);

    
    inicio = clock();
    bucketSort(arr, TAMANHO, &comparacoes, &trocas);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao BUCKETSORT:\t %f segundos\n", tempo_gasto);
    printf("TROCAS: %lld", trocas);
    printf("\nCOMPARACOES: %lld", comparacoes);
    backupArr(buffArr, arr);
        
    
    return 0;
}
