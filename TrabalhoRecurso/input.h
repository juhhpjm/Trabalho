#ifndef INPUT_H
#define INPUT_H

#define ATIVO 1
#define INATIVO 0

void cleanInputBuffer();
int obterInt(int minValor, int maxValor, char *msg);
void lerString(char *string, unsigned int tamanho, char *msg);
float obterFloat(float minValor, float maxValor, char *msg);

#endif /* INPUT_H */
