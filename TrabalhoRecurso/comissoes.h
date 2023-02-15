#ifndef COMISSOES_H
#define COMISSOES_H

#define MAX_COD_MERCADO 5
#define COMISSAO_INICIAL 7
#define MIN_ANO 1900
#define MAX_ANO 2100
#define MIN_MES 1
#define MAX_MES 12
#define MIN_DIA 1
#define MAX_DIA 31
#define MAX_MERCADOS 50


typedef struct{
    int dia, mes, ano;
}Data;

typedef struct{
    char codMercado[MAX_COD_MERCADO];
    float percentualComissao;
    Data dataInicio;
    Data dataFim;
}Comissao;

typedef struct{
    int contador, tamanho;
    Comissao *comissao;
}ListaComissao;

#endif /* COMISSOES_H */
