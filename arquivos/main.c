#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp1.h" // cabeçalho - header para TP01

int main(){
    
    int qtd;
    processo *x = le_dados("TJDFT_amostra.csv", &qtd); // Le o arquivo - (retorna vetor pelo ponteiro)

    printf("Total de processos: %d\n", qtd);
    return 0;
}