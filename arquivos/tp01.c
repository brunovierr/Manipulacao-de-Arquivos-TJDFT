#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tp01.h"

// Função auxiliar para converter string para int, tratando campos vazios
int letInt(const char *str)
{
    if (str == NULL || str[0] == '\0')
    {
        return 0; // Ou um valor padrão como -1 se 0 for um dado válido
    }
    return atoi(str);
}

// Função auxiliar para copiar strings
void lerString(char *dest, const char *src)
{
    if (src != NULL)
    {
        strcpy(dest, src);
    }
    else
    {
        dest[0] = '\0'; // Garante que a string de destino fique vazia
    }
}

// Função para contar as linhas do arquivo (mantida do seu exemplo)
int NumProcessos(const char *nomeArquivo)
{
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL)
        return 0;

    int linhas = 0;
    char buffer[CARACTERES_LINHA];
    // Ignora o cabeçalho
    if (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            linhas++;
        }
    }
    fclose(fp);
    return linhas;
}

// --- NOVA FUNÇÃO PARA EXTRAIR CAMPOS ---
// Esta função substitui o strtok e lida com campos vazios (ex: ";;")
char *obter_proximo_campo(char **ponteiro_linha, const char *delimitador)
{
    if (*ponteiro_linha == NULL)
    {
        return NULL;
    }

    char *inicio_campo = *ponteiro_linha;
    char *fim_campo = strpbrk(inicio_campo, delimitador); // Encontra o próximo delimitador

    if (fim_campo != NULL)
    {
        // Delimitador encontrado, termina o campo atual aqui
        *fim_campo = '\0';
        *ponteiro_linha = fim_campo + 1; // Avança o ponteiro para depois do delimitador
    }
    else
    {
        // Último campo da linha, não há mais delimitadores
        // Remove quebras de linha (CRLF) no final, se houver
        char *p = inicio_campo + strlen(inicio_campo) - 1;
        while (p >= inicio_campo && (*p == '\n' || *p == '\r'))
        {
            *p = '\0';
            p--;
        }
        *ponteiro_linha = NULL; // sinaliza que a linha terminou
    }

    return inicio_campo;
}

// --- SUA FUNÇÃO PRINCIPAL, AGORA CORRIGIDA ---
Processo *ler_Dados(char *nomeArquivo, int *Num)
{
    *Num = 0;

    int qtdLinhas = NumProcessos(nomeArquivo);
    if (qtdLinhas <= 0)
    {
        printf("Arquivo vazio, não encontrado ou sem dados após o cabeçalho.\n");
        return NULL; // Retornar NULL é mais seguro que `exit()`
    }

    Processo *A = malloc(qtdLinhas * sizeof(Processo));
    if (A == NULL)
    {
        printf("ERROR: não foi possível alocar memória para %d registros.\n", qtdLinhas);
        return NULL;
    }

    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL)
    {
        printf("ERROR: não foi possível abrir o arquivo\n");
        free(A);
        return NULL;
    }

    printf("Arquivo aberto com sucesso.\n");

    char linha[CARACTERES_LINHA];
    fgets(linha, CARACTERES_LINHA, fp); // Pula a linha do cabeçalho

    int i = 0;
    while (i < qtdLinhas && fgets(linha, CARACTERES_LINHA, fp))
    {
        char *ponteiro_linha = linha; // Ponteiro para a posição atual na linha
        char *token;

        // Usamos a nova função para obter cada campo
        A[i].id_processo = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        lerString(A[i].numero_sigilo, obter_proximo_campo(&ponteiro_linha, ";"));
        lerString(A[i].sigla_grau, obter_proximo_campo(&ponteiro_linha, ";"));
        lerString(A[i].procedimento, obter_proximo_campo(&ponteiro_linha, ";"));
        lerString(A[i].ramo_justica, obter_proximo_campo(&ponteiro_linha, ";"));
        lerString(A[i].sigla_tribunal, obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].id_tribunal = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].recurso = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].id_ultimo_oj = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        lerString(A[i].dt_recebimento, obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].id_ultima_classe = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].flag_violencia_domestica = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].flag_feminicidio = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].flag_ambiental = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].flag_quilombolas = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].flag_indigenas = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].flag_infancia = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        lerString(A[i].decisao, obter_proximo_campo(&ponteiro_linha, ";"));
        lerString(A[i].dt_resolvido, obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].cnm1 = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].primeirasentm1 = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].baixm1 = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].decm1 = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].mpum1 = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].julgadom1 = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].desm1 = letInt(obter_proximo_campo(&ponteiro_linha, ";"));
        A[i].susm1 = letInt(obter_proximo_campo(&ponteiro_linha, ";"));

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

int validar_e_extrair_ano(const char* data) {
    int ano, mes, dia;
    if (sscanf(data, "%d;%d;%d", &ano, &mes, &dia) == 3) {
        // Verificação básica: ano 4 dígitos (1900-2100), mes 1-12, dia 1-31
        // (ajuste os ranges conforme necessário; aqui é uma verificação simples de formato)
        if (ano >= 1900 && ano <= 2100 && mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31) {
            return ano;
        }
    }
    return -1; // Inválido
}

void processoMaisAntigo(Processo *A, int Num) {
    // o id_processo do processo com dt_recebimento mais antigo (apenas pelo ano);
    
    if (Num <= 0) {
        printf("Sem processos.\n");
        return; // sem processos
    }

    // Verificação de formato para todos os processos
    for (int i = 0; i < Num; i++) {
        int ano = validar_e_extrair_ano(A[i].dt_recebimento);
    }

    // Inicializa com o primeiro processo
    int id_antigo = A[0].id_processo;
    int ano_antigo = validar_e_extrair_ano(A[0].dt_recebimento); // Já validado acima

    // Percorre os demais processos, comparando apenas pelo ano
    for (int i = 1; i < Num; i++) {
        int ano_atual = validar_e_extrair_ano(A[i].dt_recebimento); // Já validado
        if (ano_atual < ano_antigo) {
            ano_antigo = ano_atual;
            id_antigo = A[i].id_processo;
        }
    }

    // Exemplo de saída: imprime o ID do processo mais antigo pelo ano
    // (ajuste conforme necessário; o código original não tinha saída, mas faz sentido adicionar)
    printf("Processo mais antigo (pelo ano): %d\n", id_antigo);
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

void meta1(Processo *A, int Num)
{ // o percentual de cumprimento da meta 1;
    long cnm1 = 0;
    long julgadom1 = 0;
    long desm1 = 0;
    long susm1 = 0;

    for (int i = 0; i < Num; i++)
    {
        cnm1 += A[i].cnm1;
        julgadom1 += A[i].julgadom1;
        desm1 += A[i].desm1;
        susm1 += A[i].susm1;
    }

    if ((cnm1 + desm1 - susm1) < 0)
    {
        return;
    }

    double meta1_porcentagem = (double)julgadom1 / (cnm1 + desm1 - susm1) * 100.0; // calculo meta
    printf("Cumprimento da Meta 1 = %.3f%%\n", meta1_porcentagem);
}

int novoArquivoCsv(const char *nomeArquivoOriginal, const char *arquivoNovoNome)
{ // gerar um arquivo CSV com todos os processos julgados (mérito) na Meta 1.

    FILE *primeiroArquivo = fopen(nomeArquivoOriginal, "r"); // le o arquivo tjdft
    FILE *arquivoNovo = fopen(arquivoNovoNome, "w");         // cria novo arquivo filtrado

    if (!primeiroArquivo || !arquivoNovo)
    {
        printf("Erro ao abrir arquivos!\n");
        return 1;
    }

    char linha[CARACTERES_LINHA];

    while (fgets(linha, sizeof(linha), primeiroArquivo))
    {
        char *campos[MAX_COLUNAS];
        int totalCampos = 0;

        // separa a linha em campos usando strtok
        char *ponteiro = strtok(linha, ";\n");
        while (ponteiro != NULL && totalCampos < MAX_COLUNAS)
        {
            campos[totalCampos++] = ponteiro;
            ponteiro = strtok(NULL, ";\n");
        }

        int cnm1 = 0, desm1 = 0, susm1 = 0;

        if (totalCampos > 19 && campos[19][0] != '\0')
            cnm1 = atoi(campos[19]); // atoi para comparar strings identicas
        if (totalCampos > 22 && campos[22][0] != '\0')
            desm1 = atoi(campos[22]);
        if (totalCampos > 23 && campos[23][0] != '\0')
            susm1 = atoi(campos[23]);

        if ((cnm1 + desm1 - susm1) != 0)
        {
            if (totalCampos > 21)
                campos[21][0] = '1'; // adiciona 1 a julgadom1
            if (totalCampos > 21)
                campos[21][1] = '\0';

            // escreve linha reconstruída
            for (int i = 0; i < totalCampos; i++)
            {
                fputs(campos[i], arquivoNovo);
                if (i < totalCampos - 1)
                    fputc(';', arquivoNovo);
            }
            fputc('\n', arquivoNovo);
        }
    }

    fclose(primeiroArquivo);
    fclose(arquivoNovo);
    return 0;
}
