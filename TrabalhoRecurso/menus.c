#include <stdio.h>
#include "menus.h"
#include "input.h"
#include "Mercados.h"
#include "Vendedores.h"

ListaMercado listaMercado;
ListaVendedor listaVendedor;
ListaComissao listaComissao;

void menuGestaoComissao(){
    int op;
    do{
        op=obterInt(0,2,MENU_COMISSAO);
        switch (op){
            case 1: //Atribuir
                //FuncaodeAtribuição;
            case 2: //Exibir
                //FuncaodeLista;
            case 0: //Sair
                break;
            default:
                puts("Opção Inválida. \n");
                break;
        }
    } while(op!=0);
}

void menuGestaoMercado(){
    int op;
    do{
        op=obterInt(0,5,MENU_MERCADO);
        switch (op){
            case 1: //Criar
                inserirMercado(&listaMercado);
                break;
            case 2: //Editar
                editarMercado(&listaMercado);
                break;
            case 3: //Remover
                removerMercado(&listaMercado, &listaVendedor);
                break;
            case 4: //Listar
                listarMercado(listaMercado);
                break;
            case 5: //Guardar
                guardarMercados(&listaMercado, MERCADOS_F);
                break;
            case 0: //Sair
                break;
            default:
                puts("Opção Inválida. \n");
                break;
        }
    } while(op!=0);
}

void menuGestaoVendedor(){
    int op;
    do{
        op=obterInt(0,5,MENU_VENDEDOR);
        switch (op){
            case 1: //Criar
                inserirVendedor(&listaVendedor);
                break;
            case 2: //Editar
                editarVendedor(&listaVendedor);
                break;
            case 3: //Remover
                removerVendedor(&listaVendedor);
                break;
            case 4: //Listar
                listarVendedor(listaVendedor);
                break;
            case 5: //Guardar
                guardarVendedores(&listaVendedor, VENDEDORES_F);
                break;
            case 0: //Sair
                break;
            default:
                puts("Opção Inválida. \n");
                break;
        }
    } while(op!=0);
}

void menuPrincipal(){
    int op;
    do{
        op=obterInt(0,3,MENU_PRINCIPAL);
        switch (op){
            case 1: //Gestão Vendedor
                menuGestaoVendedor();
                break;
            case 2: //Gestão Mercado
                menuGestaoMercado();
                break;
            case 3: //Gestão Comissão
                menuGestaoComissao();
                break;
            case 0: //Encerrar
                break;
            default:
                puts("Opção Inválida. \n");
                break;
        }
    } while(op!=0);
}
