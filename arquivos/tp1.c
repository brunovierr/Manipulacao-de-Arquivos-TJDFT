#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp1.h" // cabeçalho - header para TP01

// IMPLEMENTAR AS FUNÇÕES CUJO OS PROTÓTIPOS FORAM DEFINIDOS EM "tp1.h"

processo *le_dados(char *Arquivo, int *qtd){ // Inicializa o arquivo e atributos
    FILE *f = fopen(Arquivo, "r"); // Lê o arquivo

    char linha[1024];
    int processos = 0;

    fgets(linha, sizeof(linha), f); // sintaxe de fgets (inicio, fim, arquivo)

    // Lê cada linha do arquivo
    while(fgets(linha, sizeof(linha), f)) {
        processos++;
    }

    *qtd = processos;
} 