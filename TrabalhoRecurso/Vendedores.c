#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Vendedores.h"
#include "input.h"

void imprimirVendedor(Vendedor vendedor){
    int i;
    printf("\nCodigo: %s Nome: %s Email: %s Telefone: %s Estado: %d\n", vendedor.codigo, vendedor.nome,
           vendedor.email, vendedor.telefone, vendedor.estado);
    printf("Mercados associados: \n");
    for (i = 0; i < vendedor.numMercados; i++) {
        printf(" - %s\n", vendedor.comissao->codMercado);
    }
}

int procurarVendedor(ListaVendedor vendedores, char *codigo){
    int i;
    for(i=0;i<vendedores.contador;i++){
        if(strcmp(vendedores.vendedor[i].codigo, codigo)==0){
            return i;
        }
    }
    return -1;
}

void carregarVendedores(ListaVendedor *vendedores, char *ficheiro){
    int i, sucesso=0;
    FILE *fp = fopen(ficheiro, "rb");
    if(fp!=NULL){
        fread(&vendedores->contador, sizeof(int), 1, fp);
        if(vendedores->contador>0){
            vendedores->tamanho = vendedores->contador;
            vendedores->vendedor = (Vendedor*) malloc(vendedores->contador * sizeof (Vendedor));
            for(i=0; i<vendedores->contador; i++){
                fread(&vendedores->vendedor[i], sizeof(Vendedor), 1, fp);
            }
            sucesso=1;
        }
        fclose(fp);
    }
    if(!sucesso){
        fp= fopen(ficheiro, "wb");
        if(fp!=NULL){
            vendedores->vendedor = (Vendedor*) malloc(VEND_INICIAL * sizeof(Vendedor));
            vendedores->contador = 0;
            vendedores->tamanho = VEND_INICIAL;

            fclose(fp);
        }
    }
}

void guardarVendedores(ListaVendedor *vendedores, char *ficheiro){
    int i;

    FILE *fp = fopen(ficheiro, "wb");
    if(fp==NULL){
        exit(EXIT_FAILURE);
    }
    fwrite(&vendedores->contador, sizeof(int), 1, fp);
    for(i=0; i<vendedores->contador; i++){
        fwrite(&vendedores->vendedor[i], sizeof (Vendedor), 1, fp);
    }
    fclose(fp);
}

void libertarVendedor(ListaVendedor *vendedores){
    if(vendedores->vendedor){
        free(vendedores->vendedor);
        vendedores->vendedor = NULL;
    }
    vendedores = NULL;
}

int inserirDadosVendedor(ListaVendedor *vendedores){
    char codigo[MAX_CODIGO];
    lerString(codigo,MAX_CODIGO,"\nCodigo:");

    if(procurarVendedor(*vendedores, codigo)==-1){
        strcpy(vendedores->vendedor[vendedores->contador].codigo, codigo);
        lerString(vendedores->vendedor[vendedores->contador].nome, MAX_NOME, "\nNome:");
        lerString(vendedores->vendedor[vendedores->contador].email, MAX_EMAIL, "\nEmail:");
        lerString(vendedores->vendedor[vendedores->contador].telefone, MAX_TELEFONE, "\nTelefone:");
        vendedores->vendedor[vendedores->contador].estado = ATIVO;

        return vendedores->contador++;
    }
    return -1;
}

void expandirVendedor(ListaVendedor *vendedores){
    int tam= (vendedores->tamanho)==0 ? VEND_INICIAL : vendedores->tamanho *2;
    Vendedor *temp = (Vendedor*) realloc(vendedores->vendedor, sizeof(Vendedor)*(tam));
    if(temp!=NULL){
        vendedores->tamanho = tam;
        vendedores->vendedor = temp;
    }
}

void inserirVendedor(ListaVendedor *vendedores){
    if(vendedores->contador == vendedores->tamanho){
        expandirVendedor(vendedores);
    }
    if(vendedores->contador<vendedores->tamanho){
        if(inserirDadosVendedor(vendedores)==-1){
            puts("Vendedor existente.");
        }
    } else{
        puts("Não foi possível inserir um novo vendedor.");
    }
}

void editarDadosVendedor(Vendedor *vendedor){
    lerString(vendedor->nome, MAX_NOME, "\nNome:");
    lerString(vendedor->email, MAX_EMAIL, "\nEmail:");
    lerString(vendedor->telefone, MAX_TELEFONE, "\nTelefone:");
}

void editarVendedor(ListaVendedor *vendedores){
    int temp;
    char codigo[MAX_CODIGO];
    lerString(codigo, MAX_CODIGO, "\nCódigo:");
    temp = procurarVendedor(*vendedores, codigo);
    if(temp!=-1){
        editarDadosVendedor(&vendedores->vendedor[temp]);
    } else{
        puts("Vendedor não existe.");
    }
}

void listarVendedor(ListaVendedor vendedores){
    int i;
    if(vendedores.contador > 0){
        for(i=0;i<vendedores.contador;i++){
            imprimirVendedor(vendedores.vendedor[i]);
        }
    } else{
        puts("Lista Vazia");
    }
}

void apagarDadosVendedor(Vendedor *vendedor){
    strcpy(vendedor->codigo, "");
    strcpy(vendedor->nome, "");
    strcpy(vendedor->email, "");
    strcpy(vendedor->telefone, "");
    vendedor->estado = 0;
}

void removerVendedor(ListaVendedor *vendedores){
    int i, vendedor;
    char codigo[MAX_CODIGO];
    lerString(codigo,MAX_CODIGO,"\nCodigo:");

    vendedor = procurarVendedor(*vendedores,codigo);

    if(vendedor!=-1){
        if (vendedores->vendedor[vendedor].numMercados > 0) {
            vendedores->vendedor[vendedor].estado = INATIVO;
        }else {
            for (i = vendedor; i < vendedores->contador - 1; i++) {
                vendedores->vendedor[i] = vendedores->vendedor[i + 1];
            }
            apagarDadosVendedor(&vendedores->vendedor[i]);
            vendedores->contador--;
        }
    }else{
        puts("O vendedor não existe.");
    }
}