cmake_minimum_required(VERSION 3.24)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c input.h input.c menus.c menus.h Vendedores.c Vendedores.h Mercados.c Mercados.h comissoes.c comissoes.h)
