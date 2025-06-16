#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "calculadora.h"

int main() {
    char *infx = getFormaInFixa("3 4 + 5 *");
    printf("Forma Infixa: %s\n", infx);

    char *posfx = getFormaPosFixa("(3 + 4) * 5");
    printf("Forma Posfixa: %s\n", posfx);

    float valorposfx = getValorPosFixa("3 4 + 5 *");
    printf("Valor Posfixa: %.2f\n", valorposfx);

    float valorinfix = getValorInFixa("(3 + 4) * 5");
    printf("Valor Infixa: %.2f\n", valorinfix);

    return 0;
}

