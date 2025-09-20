#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processos.h"


int main() {
    system("cls");

    int Num;

    Processo * processos = ler_Dados("TJDFT_amostra.csv", &Num); // passado com & para receber alterações no * de qtd

    printf("Foram lidos %d processos.\n", Num);

    pesquisa_id_ultimo_oj(processos, &Num, 323961076); // falta fazer o gerador de planilha csv nao sei o que la
    contar_flag_violencia_domestica(processos, Num);
    contar_flag_feminicidio(processos, Num);
    contar_flag_ambiental(processos, Num);
    contar_flag_quilombolas(processos, Num);
    contar_flag_indigenas(processos, Num);
    contar_flag_infancia(processos, Num);   
    dif_dias_processo(processos,Num, 323961078);
    meta1(processos,Num,323961078);
    
    int id_antigo = processo_mais_antigo(processos, Num);

    if (id_antigo != -1)
        printf("Processo com dt_recebimento mais antigo: %d\n", id_antigo);


    free(processos);
    return 0;
}