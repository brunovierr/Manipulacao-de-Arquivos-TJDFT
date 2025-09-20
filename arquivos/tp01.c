#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tp01.h"

int NumProcessos(const char *nomeArquivo)
{ // número de processos presentes na base de dados
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp)
        return -1;

    char linha[CARACTERES_LINHA];
    int count = 0;

    if (!fgets(linha, sizeof(linha), fp))
    {
        fclose(fp);
        return 0;
    }

    while (fgets(linha, sizeof(linha), fp))
    {
        count++;
    }

    fclose(fp);
    return count;
}

void LendoString(char *dest, char *token)
{
    if (token == NULL || strlen(token) == 0)
    {
        strcpy(dest, "");
    }
    else
    {

        strcpy(dest, token);
    }
}

int LendoInt(char *token)
{
    if (token == NULL || strlen(token) == 0)
    {
        return 0;
    }
    return atoi(token);
}

Processo *ler_Dados(char *nomeArquivo, int *Num)
{
    *Num = 0;

    int qtdLinhas = NumProcessos(nomeArquivo);
    if (qtdLinhas <= 0)
    {
        printf("Arquivo vazio ou não encontrado.\n");
        exit(ERRO);
    }

    Processo *A = malloc(qtdLinhas * sizeof(Processo)); // malloc(memory alocation) para funcionamento de ponteiros
    if (A == NULL)
    {
        printf("ERROR: não foi possível alocar memória para %d registros.\n", qtdLinhas);
        exit(ERRO);
    }

    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL)
    {
        printf("ERROR: não foi possível abrir o arquivo\n");
        free(A);
        exit(ERRO);
    }

    printf("Arquivo aberto com sucesso.\n");

    char linha[CARACTERES_LINHA];

    fgets(linha, CARACTERES_LINHA, fp);

    int i = 0;
    while (fgets(linha, CARACTERES_LINHA, fp))
    {

        char *token = strtok(linha, ";");

        if (token == NULL)
        {
            printf("Linha %d inválida.\n", i);
            continue;
        }

        A[i].id_processo = LendoInt(token);
        LendoString(A[i].numero_sigilo, strtok(NULL, ";"));
        LendoString(A[i].sigla_grau, strtok(NULL, ";"));
        LendoString(A[i].procedimento, strtok(NULL, ";"));
        LendoString(A[i].ramo_justica, strtok(NULL, ";"));
        LendoString(A[i].sigla_tribunal, strtok(NULL, ";"));
        A[i].id_tribunal = LendoInt(strtok(NULL, ";"));
        A[i].recurso = LendoInt(strtok(NULL, ";"));
        A[i].id_ultimo_oj = LendoInt(strtok(NULL, ";"));
        LendoString(A[i].dt_recebimento, strtok(NULL, ";"));
        A[i].id_ultima_classe = LendoInt(strtok(NULL, ";"));
        A[i].flag_violencia_domestica = LendoInt(strtok(NULL, ";"));
        A[i].flag_feminicidio = LendoInt(strtok(NULL, ";"));
        A[i].flag_ambiental = LendoInt(strtok(NULL, ";"));
        A[i].flag_quilombolas = LendoInt(strtok(NULL, ";"));
        A[i].flag_indigenas = LendoInt(strtok(NULL, ";"));
        A[i].flag_infancia = LendoInt(strtok(NULL, ";"));
        LendoString(A[i].decisao, strtok(NULL, ";"));
        LendoString(A[i].dt_resolvido, strtok(NULL, ";"));
        A[i].cnm1 = LendoInt(strtok(NULL, ";"));
        A[i].primeirasentm1 = LendoInt(strtok(NULL, ";"));
        A[i].baixm1 = LendoInt(strtok(NULL, ";"));
        A[i].decm1 = LendoInt(strtok(NULL, ";"));
        A[i].mpum1 = LendoInt(strtok(NULL, ";"));
        A[i].julgadom1 = LendoInt(strtok(NULL, ";"));
        A[i].desm1 = LendoInt(strtok(NULL, ";"));
        A[i].susm1 = LendoInt(strtok(NULL, ";"));

        i++;
    }
    *Num = i;

    fclose(fp);
    return A;
}

void pesquisa_id_ultimo_oj(Processo *A, int *Num, int id_processo)
{ //  id_processo do processo com dt_recebimento mais antigo

    for (int i = 0; i < *Num; i++)
    {
        if (A[i].id_processo == id_processo)
        {
            printf("Ultima Orientacao Jurisprudencial (OJ): %d \t -> Processo: %d (ID DO PROCESSO).\n",
                   A[i].id_ultimo_oj, id_processo);
        }
    }
}

/* int processo_mais_antigo(Processo *A, int Num) {
    if (Num == 0) return -1; // caso não haja processos

    int i;
    int id_antigo = A[0].id_processo;
    struct tm tm_antigo = {0};
    int ano, mes, dia;

    // converte a primeira data
    if (sscanf(A[0].dt_recebimento, "%d-%d-%d", &ano, &mes, &dia) != 3) {
        printf("Formato inválido em dt_recebimento: %s\n", A[0].dt_recebimento);
        return -1;
    }
    tm_antigo.tm_year = ano - 1900;
    tm_antigo.tm_mon = mes - 1;
    tm_antigo.tm_mday = dia;
    time_t t_antigo = mktime(&tm_antigo);

    for (i = 1; i < Num; i++) {
        if (sscanf(A[i].dt_recebimento, "%d-%d-%d", &ano, &mes, &dia) != 3) {
            printf("Formato inválido em dt_recebimento: %s\n", A[i].dt_recebimento);
            continue;
        }
        struct tm tm_atual = {0};
        tm_atual.tm_year = ano - 1900;
        tm_atual.tm_mon = mes - 1;
        tm_atual.tm_mday = dia;
        time_t t_atual = mktime(&tm_atual);

        if (difftime(t_atual, t_antigo) < 0) {
            t_antigo = t_atual;
            id_antigo = A[i].id_processo;
        }
    }

    return id_antigo;
}
    */ !!!!!!!!!!!!!!!! ENTENDER COMO FUNCIONA !!!!!!!!!!!!!!!!!!!!!!

void contar_flag_violencia_domestica(Processo *A, int Num)
{ // quantos processos estão relacionadas a causas de violência doméstica
    int quantidade = 0;
    for (int i = 0; i < Num; i++)
    {
        if (A[i].flag_violencia_domestica == 1)
        {
            quantidade = quantidade + 1;
        }
    }
    printf("Quantidade de Processos relacionados a causas de violencia domestica: %d.\n", quantidade);
}

void contar_flag_feminicidio(Processo *A, int Num)
{ // quantos processos estão relacionadas a causas de feminicidio
    int quantidade = 0;
    for (int i = 0; i < Num; i++)
    {
        if (A[i].flag_feminicidio == 1)
        {
            quantidade = quantidade + 1;
        }
    }
    printf("Quantidade de Processos relacionados a causas de feminicidio: %d.\n", quantidade);
}

void contar_flag_ambiental(Processo *A, int Num)
{ // quantos processos estão relacionadas a causas ambientais
    int quantidade = 0;
    for (int i = 0; i < Num; i++)
    {
        if (A[i].flag_ambiental == 1)
        {
            quantidade++;
        }
    }
    printf("Quantidade de Processos relacionados a causas ambientais: %d.\n", quantidade);
}

void contar_flag_quilombolas(Processo *A, int Num)
{ // quantos processos estão relacionadas a causas quilombolas
    int quantidade = 0;
    for (int i = 0; i < Num; i++)
    {
        if (A[i].flag_quilombolas == 1)
        {
            quantidade++;
        }
    }
    printf("Quantidade de Processos relacionados a causas de quilombolas: %d.\n", quantidade);
}

void contar_flag_indigenas(Processo *A, int Num)
{ // quantos processos estão relacionadas a causas indígenas
    int quantidade = 0;
    for (int i = 0; i < Num; i++)
    {
        if (A[i].flag_indigenas == 1)
        {
            quantidade++;
        }
    }
    printf("Quantidade de Processos relacionados a causas indigenas: %d.\n", quantidade);
}

void contar_flag_infancia(Processo *A, int Num)
{ // quantos processos envolve causas relacionadas a infância e juventude
    int quantidade = 0;
    for (int i = 0; i < Num; i++)
    {
        if (A[i].flag_infancia == 1)
        {
            quantidade++;
        }
    }
    printf("Quantidade de Processos relacionados a causas de infancia e juventude: %d.\n", quantidade);
}

void dif_dias_processo(Processo *A, int Num, int id_processo) // número de dias entre dt_recebimento e dt_resolvido;
{
    int i;

    for (i = 0; i < Num; i++)
    {
        if (A[i].id_processo == id_processo)
        {
            struct tm tm_recebimento = {0}, tm_resolvido = {0};
            time_t t_recebimento, t_resolvido;

            int ano, mes, dia;

            // converte dt_recebimento yyyy-mm-dd
            if (sscanf(A[i].dt_recebimento, "%d-%d-%d", &ano, &mes, &dia) != 3)
            {
                printf("Formato inválido em dt_recebimento: %s\n", A[i].dt_recebimento);
            }

            tm_recebimento.tm_year = ano - 1900;
            tm_recebimento.tm_mon = mes - 1;
            tm_recebimento.tm_mday = dia;

            // converte dt_resolvido yyyy-mm-dd
            if (sscanf(A[i].dt_resolvido, "%d-%d-%d", &ano, &mes, &dia) != 3)
            {
                printf("Formato inválido em dt_resolvido: %s\n", A[i].dt_resolvido);
            }

            tm_resolvido.tm_year = ano - 1900;
            tm_resolvido.tm_mon = mes - 1;
            tm_resolvido.tm_mday = dia + 1;

            t_recebimento = mktime(&tm_recebimento);
            t_resolvido = mktime(&tm_resolvido);

            int dias = (int)(difftime(t_resolvido, t_recebimento) / (60 * 60 * 24));
            printf("Processo %d: Diferenca entre data de recebimento e data de resolucao = %d dias\n", id_processo, dias);
        }
    }
}

void meta1(Processo *A, int Num, int id_processo)
{ // o percentual de cumprimento da meta 1;
    for (int i = 0; i < Num; i++)
    {
        if (A[i].id_processo == id_processo)
        {
            int cnm1 = A[i].cnm1;
            int julgadom1 = A[i].julgadom1;
            int desm1 = A[i].desm1;
            int susm1 = A[i].susm1;

            // aq verifica se eh possivel fazer o calculo da meta1
            if ((cnm1 + desm1 - susm1) == 0)
            {
                printf("Erro: denominador zero para o processo %d\n", id_processo);
                return;
            }

            double meta1 = (double)julgadom1 / (cnm1 + desm1 - susm1) * 100.0;
            printf("Processo %d: Cumprimento da Meta 1 = %.2f%%\n", id_processo, meta1);
        }
    }
}

/*
int orgaoJulgador(Processo *x, int id_processo, int qtd) {
    for (int i = 0; i < qtd; i++)
        if (x[i].id_processo == id_processo) {
            return x[i].id_ultimo_oj;
        }
    return -1; // Processo não encontrado
}

int indiceProcessoMaisAntigo(Processo *x, int qtd) {
    if (qtd <= 0) {
        return -1;
    }

    int indiceMaisAntigo = 0;

    for (int i = 1; i < qtd; i++) {
        if (
            strcmp(x[i].dt_recebimento, x[indiceMaisAntigo].dt_recebimento) < 0
        ) {
            indiceMaisAntigo = i;
        }
    }
    return x[indiceMaisAntigo].id_processo;
}

int processosViolenciaDomestica(Processo *x, int qtd) {
    int count = 0;
    for (int i = 0; i < qtd; i++) {
        if (x[i].flag_violencia_domestica == 1) {
            count++;
        }
    }
    return count;
}



*/