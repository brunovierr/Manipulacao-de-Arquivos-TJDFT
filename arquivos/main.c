#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp1.h" // cabeçalho - header para TP01

int main() {
    int n_linhas;
    processo *X = le_dados("TJDFT_amostra.csv", &n_linhas);
    
    printf("Total de linhas lidas: %d\n", n_linhas);
}