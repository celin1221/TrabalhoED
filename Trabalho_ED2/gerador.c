#include "gerador.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para gerar números aleatórios
void gerar_aleatorio(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // Números entre 0 e 999
    }
}

// Função para gerar números em ordem crescente
void gerar_crescente(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

// Função para gerar números em ordem decrescente
void gerar_decrescente(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i - 1;
    }
}

// Função para imprimir o array
void imprimir_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
