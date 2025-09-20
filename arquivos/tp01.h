#ifndef tp01_H
#define tp01_H

#define CARACTERES_LINHA 1024 
#define ERRO -1

typedef struct {
    // ------ int's
    int id_processo;
    int id_tribunal;
    int recurso;
    int id_ultimo_oj;
    int id_ultima_classe;
    int flag_violencia_domestica;
    int flag_feminicidio;
    int flag_ambiental;
    int flag_quilombolas;
    int flag_indigenas;
    int flag_infancia;

    // ------ char's
    char numero_sigilo[50];
    char sigla_grau[20];
    char procedimento[50];
    char ramo_justica[50];
    char sigla_tribunal[10];
    char decisao[30];
    char dt_resolvido[30];
    char dt_recebimento[30];

    // ------ meta1
    int cnm1;
    int primeirasentm1;
    int baixm1;
    int decm1;
    int mpum1;
    int julgadom1;
    int desm1;
    int susm1;

} Processo;

// Funções para ler os dados do arquivo CSV e retornar um array de Processos
Processo * ler_Dados(char * nomeArquivo, int *qtd);
void pesquisa_id_ultimo_oj(Processo *A, int *Num, int id_processo);
void contar_flag_violencia_domestica(Processo *A, int Num);
void contar_flag_feminicidio(Processo *A, int Num);
void contar_flag_ambiental(Processo *A, int Num);
void contar_flag_quilombolas(Processo *A, int Num);
void contar_flag_indigenas(Processo *A, int Num);
void contar_flag_infancia(Processo *A, int Num);
void dif_dias_processo(Processo *A, int Num, int id_processo);
void meta1(Processo *A, int Num, int id_processo);
int processo_mais_antigo(Processo *A, int Num);

#endif
