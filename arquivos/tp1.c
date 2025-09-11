#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp1.h" // cabeçalho - header para TP01

// IMPLEMENTAR AS FUNÇÕES CUJO OS PROTÓTIPOS FORAM DEFINIDOS EM "tp1.h"
processo* le_dados(char *Arquivo, int *num_linhas){
    FILE *fp = fopen(Arquivo, "r");
    if (fp == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        exit(1);
    }
    printf("Arquivo aberto com sucesso.\n");

    char colunas[330];
    fgets(colunas, sizeof(colunas), fp); // lê e descarta o cabeçalho

    int capacidade = 10; // capacidade inicial do array
    processo *X = malloc(capacidade * sizeof(processo));
    if (X == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    int i = 0;
    while (1) {
        if (i >= capacidade) {
            capacidade *= 2; // dobra a capacidade
            processo *temp = realloc(X, capacidade * sizeof(processo));
            if (temp == NULL) {
                printf("Erro ao realocar memória.\n");
                free(X);
                exit(1);
            }
            X = temp;
        }

        int campos_lidos = fscanf(fp, "%d;sigiloso(%d);%9[^;];%99[^;];%49[^;];%9[^;];%d;%d;%d;%19[^;];%d;%d;%d;%d;%d;%d;%d;%d;%19[^;];%d;%d;%d;%d;%d;%d;%d;%d",
            &X[i].id_processo,
            &X[i].numero_sigilo,
            X[i].sigla_grau,
            X[i].procedimento,
            X[i].ramo_justica,
            X[i].sigla_tribunal,
            &X[i].id_tribunal,
            &X[i].recurso,
            &X[i].id_ultimo_oj,
            X[i].dt_recebimento,
            &X[i].id_ultima_classe,
            &X[i].flag_violencia_domestica,
            &X[i].flag_feminicidio,
            &X[i].flag_ambiental,
            &X[i].flag_quilombolas,
            &X[i].flag_indigenas,
            &X[i].flag_infancia,
            &X[i].decisao,
            X[i].dt_resolvido,
            &X[i].cnm1,
            &X[i].primeirasentm1,
            &X[i].baixm1,
            &X[i].decm1,
            &X[i].mpum1,
            &X[i].julgadom1,
            &X[i].desm1,
            &X[i].susm1);

        if (campos_lidos != 28) {
            break; 
        }
        i++;
    }

    fclose(fp);

    *num_linhas = i;
    return X;
}
