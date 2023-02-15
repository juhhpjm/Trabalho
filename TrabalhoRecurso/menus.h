#ifndef MENUS_H
#define MENUS_H

#define MENU_PRINCIPAL "Menu Principal:\n 1.Gestão de Vendedores\n 2.Gestão de Mercados\n\
3.Gestão de Comissões\n 0.Fechar Programa\n"
#define MENU_VENDEDOR "Gestão de Vendedores:\n 1.Criar\n 2.Editar\n 3.Remover\n\
4.Listar\n 5.Guardar\n 0.Sair\n"
#define MENU_MERCADO "Gestão de Mercados:\n 1.Criar\n 2.Editar\n 3.Remover\n\
4.Listar\n 5.Guardar\n 0.Sair\n"
#define MENU_COMISSAO "1.Atribuir Comissão\n 2.Exibir Comissões\n 3.Guardar\n\
0.Sair\n"

#define VENDEDORES_F "vendedores.bin"
#define MERCADOS_F "mercados.bin"

void menuGestaoComissao();
void menuGestaoMercado();
void menuGestaoVendedor();
void menuPrincipal();



#endif /* MENUS_H */
