#include "gerador.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 10

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

int main() {
    int opcao;
    int arr[TAMANHO];
       
    printf("Escolha a opcao:\n");
    printf("1 - Ordem Aleatoria\n2 - Ordem Crescente\n3 - Ordem Decrescente\n");
    scanf("%d", &opcao);
    
    srand(time(NULL));
    
    switch (opcao) {
        case 1:
            gerar_aleatorio(arr, TAMANHO);
            break;
        case 2:
            gerar_crescente(arr, TAMANHO);
            break;
        case 3:
            gerar_decrescente(arr, TAMANHO);
            break;
        default:
            printf("Opção inválida!\n");
            return 1;
    }
    
    imprimir_array(arr, TAMANHO);
    bolhaParada(arr, TAMANHO);
    imprimir_array(arr, TAMANHO);
    insercaoBinaria(arr, TAMANHO);
    imprimir_array(arr, TAMANHO);
    selecaoDireta(arr, TAMANHO);
    imprimir_array(arr, TAMANHO);
    return 0;
}
