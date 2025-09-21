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

void lerString(char *dest, char *token)
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

int letInt(char *token)
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
            continue; // pula para proxima linha
        }

        A[i].id_processo = letInt(token);
        lerString(A[i].numero_sigilo, strtok(NULL, ";"));
        lerString(A[i].sigla_grau, strtok(NULL, ";"));
        lerString(A[i].procedimento, strtok(NULL, ";"));
        lerString(A[i].ramo_justica, strtok(NULL, ";"));
        lerString(A[i].sigla_tribunal, strtok(NULL, ";"));
        A[i].id_tribunal = letInt(strtok(NULL, ";"));
        A[i].recurso = letInt(strtok(NULL, ";"));
        A[i].id_ultimo_oj = letInt(strtok(NULL, ";"));
        lerString(A[i].dt_recebimento, strtok(NULL, ";"));
        A[i].id_ultima_classe = letInt(strtok(NULL, ";"));
        A[i].flag_violencia_domestica = letInt(strtok(NULL, ";"));
        A[i].flag_feminicidio = letInt(strtok(NULL, ";"));
        A[i].flag_ambiental = letInt(strtok(NULL, ";"));
        A[i].flag_quilombolas = letInt(strtok(NULL, ";"));
        A[i].flag_indigenas = letInt(strtok(NULL, ";"));
        A[i].flag_infancia = letInt(strtok(NULL, ";"));
        lerString(A[i].decisao, strtok(NULL, ";"));
        lerString(A[i].dt_resolvido, strtok(NULL, ";"));
        A[i].cnm1 = letInt(strtok(NULL, ";"));
        A[i].primeirasentm1 = letInt(strtok(NULL, ";"));
        A[i].baixm1 = letInt(strtok(NULL, ";"));
        A[i].decm1 = letInt(strtok(NULL, ";"));
        A[i].mpum1 = letInt(strtok(NULL, ";"));
        A[i].julgadom1 = letInt(strtok(NULL, ";"));
        A[i].desm1 = letInt(strtok(NULL, ";"));
        A[i].susm1 = letInt(strtok(NULL, ";"));

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
            printf("ID Ultima Orientacao Jurisprudencial (OJ): %d\t -> Processo: %d (ID DO PROCESSO).\n",
                   A[i].id_ultimo_oj, id_processo);
        }
    }
}

void processoMaisAntigo(Processo *A, int Num) { // o id_processo do processo com dt_recebimento mais antigo;
    if (Num <= 0){
        printf("Sem processos.\n");
    } // sem processos

    int id_antigo = A[0].id_processo;
    char dt_antiga[30];
    strcpy(dt_antiga, A[0].dt_recebimento);

    for (int i = 1; i < Num; i++) {
        if (strcmp(A[i].dt_recebimento, dt_antiga) < 0) {
            strcpy(dt_antiga, A[i].dt_recebimento);
            id_antigo = A[i].id_processo;
        }
    }

    printf("Processo mais antigo: %d. (%s)\n", id_antigo, dt_antiga);
}

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

            // verifica se possível realizar o calculo da meta (csm, desm e susm maiores que 0)
            if ((cnm1 + desm1 + susm1) == 0)
            {
                printf("Erro: denominador zero para o processo %d, impossivel realizar o calculo da meta.\n", id_processo);
                return;
            }

            double meta1 = (double)julgadom1 / (cnm1 + desm1 - susm1) * 100.0; // calculo meta
            printf("Processo %d: Cumprimento da Meta 1 = %.2f%%\n", id_processo, meta1);
        }
    }
}

int novoArquivoCsv(const char *nomeArquivoOriginal, const char *arquivoNovoNome) { // gerar um arquivo CSV com todos os processos julgados (mérito) na Meta 1.

    FILE *primeiroArquivo = fopen(nomeArquivoOriginal, "r"); // le o arquivo tjdft
    FILE *arquivoNovo   = fopen(arquivoNovoNome, "w"); // cria novo arquivo filtrado

    if (!primeiroArquivo || !arquivoNovo) {
        printf("Erro ao abrir arquivos!\n");
        return 1;
    }

    char linha[CARACTERES_LINHA];

    while (fgets(linha, sizeof(linha), primeiroArquivo)) {
        char *campos[MAX_COLUNAS];
        int totalCampos = 0;

        // separa a linha em campos usando strtok
        char *ponteiro = strtok(linha, ";\n");
        while (ponteiro != NULL && totalCampos < MAX_COLUNAS) {
            campos[totalCampos++] = ponteiro;
            ponteiro = strtok(NULL, ";\n");
        }

        int cnm1 = 0, desm1 = 0, susm1 = 0;

        if (totalCampos > 19 && campos[19][0] != '\0') cnm1 = atoi(campos[19]); // atoi para comparar strings identicas
        if (totalCampos > 22 && campos[22][0] != '\0') desm1 = atoi(campos[22]);
        if (totalCampos > 23 && campos[23][0] != '\0') susm1 = atoi(campos[23]);

        if ((cnm1 + desm1 - susm1) != 0) {
            if (totalCampos > 21) campos[21][0] = '1'; // adiciona 1 a julgadom1
            if (totalCampos > 21) campos[21][1] = '\0';

            // escreve linha reconstruída
            for (int i = 0; i < totalCampos; i++) {
                fputs(campos[i], arquivoNovo);
                if (i < totalCampos - 1) fputc(';', arquivoNovo);
            }
            fputc('\n', arquivoNovo);
        }
    }

    fclose(primeiroArquivo);
    fclose(arquivoNovo);
    return 0;
}
