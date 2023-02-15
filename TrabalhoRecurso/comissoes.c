#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comissoes.h"
#include "Vendedores.h"
#include "Mercados.h"
#include "input.h"

void carregarComissao(ListaComissao *comissoes, char *ficheiro){
    int i, sucesso=0;
    FILE *fp = fopen(ficheiro, "rb");
    if(fp!=NULL){
        fread(&comissoes->contador, sizeof(int), 1, fp);
        if(comissoes->contador>0){
            comissoes->tamanho = comissoes->contador;
            comissoes->comissao = (Comissao *) malloc(comissoes->contador * sizeof (Comissao));
            for(i=0; i<comissoes->contador; i++){
                fread(&comissoes->comissao[i], sizeof(Comissao), 1, fp);
            }
            sucesso=1;
        }
        fclose(fp);
    }
    if(!sucesso){
        fp= fopen(ficheiro, "wb");
        if(fp!=NULL){
            comissoes->comissao = (Comissao *) malloc(COMISSAO_INICIAL* sizeof(Comissao));
            comissoes->contador = 0;
            comissoes->tamanho = COMISSAO_INICIAL;

            fclose(fp);
        }
    }
}

void guardarComissao(ListaComissao *comissoes, char *ficheiro){
    int i;
    FILE *fp = fopen(ficheiro, "wb");
    if(fp==NULL){
        exit(EXIT_FAILURE);
    }
    fwrite(&comissoes->contador, sizeof(int), 1, fp);
    for(i=0; i<comissoes->contador; i++){
        fwrite(&comissoes->comissao[i], sizeof (Comissao), 1, fp);
    }
    fclose(fp);
}

int dataSobreposta(Data dataInicio1, Data dataFim1, Data dataInicio2, Data dataFim2) {
    if ((dataInicio1.ano < dataInicio2.ano) ||
        (dataInicio1.ano == dataInicio2.ano && dataInicio1.mes < dataInicio2.mes) ||
        (dataInicio1.ano == dataInicio2.ano && dataInicio1.mes == dataInicio2.mes && dataInicio1.dia< dataInicio2.dia)) {
        if ((dataFim1.ano < dataInicio2.ano) ||
            (dataFim1.ano == dataInicio2.ano && dataFim1.mes < dataInicio2.mes) ||
            (dataFim1.ano == dataInicio2.ano && dataFim1.mes == dataInicio2.mes && dataFim1.dia < dataInicio2.dia)) {
            return 0;
        }
    } else if ((dataInicio1.ano > dataFim2.ano) ||
               (dataInicio1.ano == dataFim2.ano && dataInicio1.mes > dataFim2.mes) ||
               (dataInicio1.ano == dataFim2.ano && dataInicio1.mes == dataFim2.mes && dataInicio1.dia > dataFim2.dia)) {
        if ((dataFim1.ano > dataFim2.ano) ||
            (dataFim1.ano == dataFim2.ano && dataFim1.mes > dataFim2.mes) ||
            (dataFim1.ano == dataFim2.ano && dataFim1.mes == dataFim2.mes && dataFim1.dia > dataFim2.dia)) {
            return 0;
        }
    }
    return 1;
}

int dataMenorOuIgual(Data data1, Data data2) {
    if (data1.ano < data2.ano) {
        return 1;
    } else if (data1.ano > data2.ano) {
        return 0;
    } else if (data1.mes < data2.mes) {
        return 1;
    } else if (data1.mes > data2.mes) {
        return 0;
    } else if (data1.dia <= data2.dia) {
        return 1;
    } else {
        return 0;
    }
}

int atribuirMercadoVendedorComissao(ListaVendedor *listaVendedor, ListaMercado *listaMercado, ListaComissao *listaComissao) {
    int mercado, vendedor, contadorMercado = 0;
    Data dataInicio;
    Data dataFim;
    char codigoVendedor[MAX_CODIGO];
    char codigoMercado[MAX_CODIGO];

    lerString(codigoMercado, MAX_CODIGO, "\nInsira o código do mercado:");
    mercado = procurarMercado(*listaMercado, codigoMercado);

    if (!mercado) {
        printf("Mercado não encontrado.\n");
        return 0;
    }
    lerString(codigoVendedor, MAX_CODIGO, "\nInsira o código do Vendedor:");
    vendedor = procurarVendedor(*listaVendedor, codigoVendedor);

    if (!vendedor) {
        printf("Vendedor não encontrado.\n");
        return 0;
    }
    puts("Data de Inicio:");
    dataInicio.dia = obterInt(MIN_DIA,MAX_DIA,"\nDia:");
    dataInicio.mes = obterInt(MIN_MES,MAX_MES, "\nMês:");
    dataInicio.ano = obterInt(MIN_ANO, MAX_ANO, "\nAno:");
    puts("Data do Final:");
    dataFim.dia = obterInt(MIN_DIA, MAX_DIA, "\nDia:");
    dataFim.mes = obterInt(MIN_MES, MAX_MES, "\nMês:");
    dataFim.ano = obterInt(MIN_ANO, MAX_ANO, "\nAno:");

    if (!dataMenorOuIgual(dataInicio, dataFim)) {
        printf("Data de inicio posterior a data de fim\n");
        return 0;
    }
    for (int i = 0; i < listaVendedor->vendedor->numMercados; i++) {
        if (strcmp(listaVendedor->vendedor[vendedor].comissao[i].codMercado, codigoMercado) == 0) {
            printf("O vendedor ja esta associado ao mercado %s\n", codigoMercado);
            return 0;
        }
        if (dataSobreposta(listaVendedor->vendedor[vendedor].comissao[i].dataInicio,
                           listaVendedor->vendedor[vendedor].comissao[i].dataFim,
                           dataInicio, dataFim)) {
            printf("Sobreposicao de datas.");
            return 0;
        }
    }
    if (listaVendedor->vendedor->numMercados >= MAX_MERCADOS) {
        printf("O vendedor ja esta associado ao maximo de mercados permitidos (%d)\n", MAX_MERCADOS);
        return 0;
    }
    contadorMercado = listaVendedor->vendedor[vendedor].numMercados;
    strcpy(listaVendedor->vendedor[vendedor].comissao[contadorMercado].codMercado, codigoMercado);
    listaVendedor->vendedor[vendedor].comissao[contadorMercado].percentualComissao = obterFloat(10,90,"Insira a percentagem de Comissão:\n");
    listaVendedor->vendedor[vendedor].comissao[contadorMercado].dataInicio = dataInicio;
    listaVendedor->vendedor[vendedor].comissao[contadorMercado].dataFim = dataFim;

    return listaVendedor->vendedor[vendedor].numMercados++;
}

void expandirComissao(ListaComissao *comissoes){
    int tam= (comissoes->tamanho)==0 ? COMISSAO_INICIAL : comissoes->tamanho *2;
    Comissao *temp = (Comissao*) realloc(comissoes->comissao, sizeof(Comissao)*(tam));
    if(temp!=NULL){
        comissoes->tamanho = tam;
        comissoes->comissao = temp;
    }
}

void atribuirComissao(ListaComissao *comissoes, ListaMercado *mercados, ListaVendedor *vendedores){
    if(comissoes->contador == comissoes->tamanho){
        expandirVendedor(comissoes);
    }
    if(comissoes->contador<comissoes->tamanho){
        if(!atribuirMercadoVendedorComissao(vendedores, mercados, comissoes)){
            puts("Vendedor existente.");
        }
    } else{
        puts("Não foi possível inserir um novo vendedor.");
    }
}
