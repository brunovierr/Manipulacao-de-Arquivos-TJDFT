# Atividade Manipulação de Arquivos em C 🤯

> *por Lucas Alves e Bruno de França*

# Explicação do Código de Processamento de Arquivo de Processos

Este documento descreve, de forma resumida, como foi construído e utilizado cada parte do código-fonte fornecido.  

---

## 📌 Função `NumProcessos`

```c
int NumProcessos(const char *nomeArquivo)
{
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
```

🔎 **Descrição**:  
Aqui foi usada a função para contar quantas linhas existem no arquivo CSV (excluindo o cabeçalho).  
- Retornamos `-1` caso o arquivo não seja encontrado.  
- Retornamos `0` caso o arquivo esteja vazio.  

---

## 📌 Função `lerString`

```c
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
```

🔎 **Descrição**:  
Foi usada para copiar uma string lida do arquivo (`token`) para o destino (`dest`).  
Quando encontramos um campo vazio, usamos uma string vazia no lugar.  

---

## 📌 Função `letInt`

```c
int letInt(char *token)
{
    if (token == NULL || strlen(token) == 0)
    {
        return 0;
    }
    return atoi(token);
}
```

🔎 **Descrição**:  
Foi usada para converter uma string (`token`) em número inteiro.  
Se o campo estava vazio, usamos `0`.  

---

## 📌 Função `ler_Dados`

```c
Processo *ler_Dados(char *nomeArquivo, int *Num)
{
    ...
}
```

🔎 **Descrição**:  
Nesta função foi usado o processo de leitura de todo o arquivo CSV.  
Usamos `malloc` para alocar memória dinamicamente e armazenar todos os registros em um vetor de `Processo`.  
No final, salvamos em `*Num` a quantidade de registros lidos.  

---

## 📌 Função `pesquisa_id_ultimo_oj`

```c
void pesquisa_id_ultimo_oj(Processo *A, int *Num, int id_processo)
{
    for (int i = 0; i < *Num; i++)
    {
        if (A[i].id_processo == id_processo)
        {
            printf("ID Ultima Orientacao Jurisprudencial (OJ): %d\t -> Processo: %d (ID DO PROCESSO).\n",
                   A[i].id_ultimo_oj, id_processo);
        }
    }
}
```

🔎 **Descrição**:  
Aqui usamos um `for` para procurar o processo com o `id_processo` indicado e exibimos seu campo `id_ultimo_oj`.  

---

## 📌 Função `processoMaisAntigo`

```c
void processoMaisAntigo(Processo *A, int Num)
{
    if (Num <= 0){
        printf("Sem processos.\n");
    }

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
```

🔎 **Descrição**:  
Foi usada para comparar todas as datas de recebimento e encontrar o processo mais antigo.  
Usamos `strcmp` para comparar as datas em formato de string.  

---

## 📌 Funções de Contagem de Flags

Exemplo:

```c
void contar_flag_violencia_domestica(Processo *A, int Num)
{
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
```

🔎 **Descrição**:  
Aqui foram usadas várias funções semelhantes (`contar_flag_violencia_domestica`, `contar_flag_feminicidio`, `contar_flag_ambiental`, `contar_flag_quilombolas`, `contar_flag_indigenas`, `contar_flag_infancia`).  
Cada uma conta quantos processos tinham a flag específica igual a **1**.  

---

## 📌 Função `dif_dias_processo`

```c
void dif_dias_processo(Processo *A, int Num, int id_processo)
{
    for (int i = 0; i < Num; i++)
    {
        if (A[i].id_processo == id_processo)
        {
            struct tm tm_recebimento = {0}, tm_resolvido = {0};
            time_t t_recebimento, t_resolvido;

            int ano, mes, dia;

            if (sscanf(A[i].dt_recebimento, "%d-%d-%d", &ano, &mes, &dia) != 3)
            {
                printf("Formato inválido em dt_recebimento: %s\n", A[i].dt_recebimento);
            }

            tm_recebimento.tm_year = ano - 1900;
            tm_recebimento.tm_mon = mes - 1;
            tm_recebimento.tm_mday = dia;

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
```

🔎 **Descrição**:  
Foi usada para calcular a diferença em dias entre a data de recebimento e a data de resolução de um processo.  
Usamos `mktime` e `difftime` para converter as datas e calcular o intervalo.  

---

## 📌 Função `meta1`

```c
void meta1(Processo *A, int Num, int id_processo)
{
    for (int i = 0; i < Num; i++)
    {
        if (A[i].id_processo == id_processo)
        {
            int cnm1 = A[i].cnm1;
            int julgadom1 = A[i].julgadom1;
            int desm1 = A[i].desm1;
            int susm1 = A[i].susm1;

            if ((cnm1 + desm1 + susm1) == 0)
            {
                printf("Erro: denominador zero para o processo %d, impossivel realizar o calculo da meta.\n", id_processo);
                return;
            }

            double meta1 = (double)julgadom1 / (cnm1 + desm1 - susm1) * 100.0;
            printf("Processo %d: Cumprimento da Meta 1 = %.2f%%\n", id_processo, meta1);
        }
    }
}
```

🔎 **Descrição**:  
Aqui usamos os valores de `cnm1`, `julgadom1`, `desm1` e `susm1` para calcular o percentual da **Meta 1**.  
Foi usado um cálculo percentual para mostrar a taxa de cumprimento da meta em cada processo.  

---

## 📌 Função `novoArquivoCsv`

```c
int novoArquivoCsv(const char *nomeArquivoOriginal, const char *arquivoNovoNome)
{
    ...
}
```

🔎 **Descrição**:  
Nesta parte usamos dois arquivos: o original e o novo.  
Foi usada a lógica de filtrar apenas os processos julgados que atendiam à **Meta 1**, e então escrevemos esses registros em um **novo arquivo CSV**.  

---
