#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tp01.h"


int main() {
    system("cls"); // começa limpando o terminal

    int Num;

    const char *arquivoOriginal = "TJDFT_filtrado.csv"; // csv original
    const char *arquivoFiltrado = "processosJulgados.csv"; // novo arquivo

    Processo * processos = ler_Dados("TJDFT_filtrado.csv", &Num); // passado com & para receber alterações no ponteiro de num

    printf("Foram lidos %d processos no total.\n", Num);

    pesquisa_id_ultimo_oj(processos, &Num, 323961076);
    processoMaisAntigo(processos, Num);
    contar_flag_violencia_domestica(processos, Num);
    contar_flag_feminicidio(processos, Num);
    contar_flag_ambiental(processos, Num);
    contar_flag_quilombolas(processos, Num);
    contar_flag_indigenas(processos, Num);
    contar_flag_infancia(processos, Num);   
    dif_dias_processo(processos,Num, 323961068);
    meta1(processos,Num);

    if (novoArquivoCsv(arquivoOriginal, arquivoFiltrado) == 0) {
        printf("\n-- Arquivo '%s' gerado com sucesso! --", arquivoFiltrado);
    } else {
        printf("\nFalha ao gerar o arquivo filtrado.");
    }

    free(processos); // libera memória de "processos"
    return 0;
}