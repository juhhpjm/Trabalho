#ifndef MERCADOS_H
#define MERCADOS_H
#include "Vendedores.h"

#define MERCADO_INICIAL 5

typedef struct{
    char codigo[MAX_CODIGO];
    char nome[MAX_NOME];
    int estado;
}Mercado;

typedef struct{
    int contador,tamanho;
    Mercado *mercado;
}ListaMercado;

void imprimirMercado(Mercado mercado);
int procurarMercado(ListaMercado mercados, char *codigo);
void carregarMercado(ListaMercado *mercados, char *ficheiro);
void guardarMercados(ListaMercado *mercados, char *ficheiro);
void libertarMercado(ListaMercado *mercados);
int inserirDadosMercado(ListaMercado *mercados);
void expandirMercado(ListaMercado *mercados);
void inserirMercado(ListaMercado *mercados);
void editarDadosMercado(Mercado *mercado);
void editarMercado(ListaMercado *mercados);
void listarMercado(ListaMercado mercados);
void apagarDadosMercado(Mercado *mercado);
void removerMercado(ListaMercado *mercados,ListaVendedor *vendedores);

#endif /*MERCADOS_H*/
