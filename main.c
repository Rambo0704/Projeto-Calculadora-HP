#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "calculadora.h"

int main() {
    Expressao expressao;
    strcpy(expressao.posFixa, "3 12 4 + *");

    char* resultado = getFormaInFixa(expressao.posFixa); // Captura o resultado

    // Armazena no campo infixo da struct
    strcpy(expressao.inFixa, resultado);

    printf("Expressao em forma pos-fixa: %s\n", expressao.posFixa);
    printf("Expressao convertida para infixa: %s\n", expressao.inFixa);

    return 0;
}
