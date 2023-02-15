#ifndef VENDEDORES_H
#define VENDEDORES_H
#include "comissoes.h"

#define MAX_CODIGO 6
#define MAX_NOME 51
#define MAX_EMAIL 51
#define MAX_TELEFONE 11
#define VEND_INICIAL 5

typedef struct{
    char codigo[MAX_CODIGO];
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char telefone[MAX_TELEFONE];
    int estado;
    Comissao *comissao;
    int numMercados;
}Vendedor;

typedef struct{
    int contador, tamanho;
    Vendedor *vendedor;
}ListaVendedor;

void imprimirVendedor(Vendedor vendedor);
int procurarVendedor(ListaVendedor vendedores, char *codigo);
void carregarVendedores(ListaVendedor *vendedores, char *ficheiro);
void guardarVendedores(ListaVendedor *vendedores, char *ficheiro);
void libertarVendedor(ListaVendedor *vendedores);
int inserirDadosVendedor(ListaVendedor *vendedores);
void expandirVendedor(ListaVendedor *vendedores);
void inserirVendedor(ListaVendedor *vendedores);
void editarDadosVendedor(Vendedor *vendedor);
void editarVendedor(ListaVendedor *vendedores);
void listarVendedor(ListaVendedor vendedores);
void apagarDadosVendedor(Vendedor *vendedor);
void removerVendedor(ListaVendedor *vendedores);
#endif /* VENDEDORES_H */
