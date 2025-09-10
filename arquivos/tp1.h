#ifndef TP1_H
#define TP1_H


/* PROTÓTIPOS E STRUCTS */

typedef struct {
    // atributos de texto.
    int id_processo[50];
    int numero_sigilo[50];
    char sigla_grau[5];
    char procedimento[100];
    char ramo_justica[5];
    char sigla_tribunal[10];
    char recurso[5];
    int id_ultimo_oj[50];
    int id_ultima_classe[50];
    
    // datas
    char dt_recebimento[20];
    char dt_julgamento[20];
    char decisao[20];
    char dt_resolvido[20];

    // atributos numéricos.
    int id_tribunal;

    // flags temáticas
    int flag_violencia_domestica;
    int flag_feminicidio;
    int flag_ambiental;
    int flag_quilombolas;
    int flag_indigenas;
    int flag_infancia;

    // meta1 
    int cnm1;
    int primeirasentm1;
    int baixm1;
    int decm1;
    int mpum1;
    int julgadom1;
    int desm1;
    int susm1;

} processo


#endif