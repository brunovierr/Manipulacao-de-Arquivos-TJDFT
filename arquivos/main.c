#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tp01.h"


int main() {
    system("cls"); // começa limpando o terminal

    int Num;

    const char *arquivoOriginal = "TJDFT_amostra.csv"; // csv original
    const char *arquivoFiltrado = "processosJulgados.csv"; // novo arquivo

    if (novoArquivoCsv(arquivoOriginal, arquivoFiltrado) == 0) {
        printf("Arquivo '%s' gerado com sucesso!\n", arquivoFiltrado);
    } else {
        printf("Falha ao gerar o arquivo filtrado.\n");
    }

    Processo * processos = ler_Dados("TJDFT_amostra.csv", &Num); // passado com & para receber alterações no ponteiro de qtd

    printf("Foram lidos %d processos no total.\n", Num);

    pesquisa_id_ultimo_oj(processos, &Num, 323961076);
    processoMaisAntigo(processos, Num);
    contar_flag_violencia_domestica(processos, Num);
    contar_flag_feminicidio(processos, Num);
    contar_flag_ambiental(processos, Num);
    contar_flag_quilombolas(processos, Num);
    contar_flag_indigenas(processos, Num);
    contar_flag_infancia(processos, Num);   
    dif_dias_processo(processos,Num, 323961069);
    meta1(processos,Num,323961063);

    free(processos); // libera memória de "processos"
    return 0;
}