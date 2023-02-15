#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "Mercados.h"

void imprimirMercado(Mercado mercado){
    printf("\nCodigo: %s Nome: %s Estado: %d", mercado.codigo, mercado.nome, mercado.estado);
}

int procurarMercado(ListaMercado mercados, char *codigo){
    int i;
    for(i=0;i<mercados.contador;i++){
        if(strcmp(mercados.mercado[i].codigo, codigo)==0){
            return i;
        }
    }
    return -1;
}

void carregarMercado(ListaMercado *mercados, char *ficheiro){
    int i, sucesso=0;
    FILE *fp = fopen(ficheiro, "rb");
    if(fp!=NULL){
        fread(&mercados->contador, sizeof(int), 1, fp);
        if(mercados->contador>0){
            mercados->tamanho = mercados->contador;
            mercados->mercado = (Mercado *) malloc(mercados->contador * sizeof (Mercado));
            for(i=0; i<mercados->contador; i++){
                fread(&mercados->mercado[i], sizeof(Mercado), 1, fp);
            }
            sucesso=1;
        }
        fclose(fp);
    }
    if(!sucesso){
        fp= fopen(ficheiro, "wb");
        if(fp!=NULL){
            mercados->mercado = (Mercado *) malloc(MERCADO_INICIAL * sizeof(Mercado));
            mercados->contador = 0;
            mercados->tamanho = MERCADO_INICIAL;

            fclose(fp);
        }
    }
}

void guardarMercados(ListaMercado *mercados, char *ficheiro){
    int i;

    FILE *fp = fopen(ficheiro, "wb");
    if(fp==NULL){
        exit(EXIT_FAILURE);
    }
    fwrite(&mercados->contador, sizeof(int), 1, fp);
    for(i=0; i<mercados->contador; i++){
        fwrite(&mercados->mercado[i], sizeof (Mercado), 1, fp);
    }
    fclose(fp);
}

void libertarMercado(ListaMercado *mercados){
    if(mercados->mercado){
        free(mercados->mercado);
        mercados->mercado = NULL;
    }
    mercados = NULL;
}

int inserirDadosMercado(ListaMercado *mercados){
    char codigo[MAX_CODIGO];
    lerString(codigo,MAX_CODIGO,"\nCodigo:");

    if(procurarMercado(*mercados, codigo)==-1){
        strcpy(mercados->mercado[mercados->contador].codigo, codigo);
        lerString(mercados->mercado[mercados->contador].nome, MAX_NOME, "\nNome:");
        mercados->mercado[mercados->contador].estado = ATIVO;

        return mercados->contador++;
    }
    return -1;
}

void expandirMercado(ListaMercado *mercados){
    int tam= (mercados->tamanho)==0 ? MERCADO_INICIAL : mercados->tamanho *2;
    Mercado *temp = (Mercado*) realloc(mercados->mercado, sizeof(Mercado)*(tam));
    if(temp!=NULL){
        mercados->tamanho = tam;
        mercados->mercado = temp;
    }
}

void inserirMercado(ListaMercado *mercados){
    if(mercados->contador == mercados->tamanho){
        expandirMercado(mercados);
    }
    if(mercados->contador<mercados->tamanho){
        if(inserirDadosMercado(mercados)==-1){
            puts("Mercado existente.");
        }
    } else{
        puts("Não foi possível inserir um novo mercado.");
    }
}

void editarDadosMercado(Mercado *mercado){
    lerString(mercado->nome, MAX_NOME, "\nNome:");
}

void editarMercado(ListaMercado *mercados){
    int temp;
    char codigo[MAX_CODIGO];
    lerString(codigo, MAX_CODIGO, "\nCódigo:");
    temp = procurarMercado(*mercados, codigo);
    if(temp!=-1){
        editarDadosMercado(&mercados->mercado[temp]);
    } else{
        puts("Vendedor não existe.");
    }
}

void listarMercado(ListaMercado mercados){
    int i;
    if(mercados.contador > 0){
        for(i=0;i<mercados.contador;i++){
            imprimirMercado(mercados.mercado[i]);
        }
    } else{
        puts("Lista Vazia.");
    }
}

void apagarDadosMercado(Mercado *mercado){
    strcpy(mercado->codigo, "");
    strcpy(mercado->nome, "");
    mercado->estado = 0;
}

void removerMercado(ListaMercado *mercados, ListaVendedor *vendedores){
    int i, mercado, associado=0;
    char codigo[MAX_CODIGO];
    lerString(codigo,MAX_CODIGO,"\nCodigo:");

    mercado = procurarMercado(*mercados,codigo);

    if(mercado!=-1){
        for (i = 0; i < vendedores->contador; i++) {
            for (int j = 0; j < vendedores->vendedor[i].numMercados; j++) {
                if (strcmp(vendedores->vendedor[i].comissao[j].codMercado,codigo) == 0) {
                    associado = 1;
                    break;
                }
            }
        }
        if (associado) {
            mercados->mercado[mercado].estado = INATIVO;
        } else {
            for(i=mercado; i< mercados->contador-1; i++){
                mercados->mercado[i] = mercados->mercado[i+1];
            }
            apagarDadosMercado(&mercados->mercado[i]);
            mercados->contador--;
        }
    }else{
        puts("O mercado não existe.");
    }
}


