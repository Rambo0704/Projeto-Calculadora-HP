#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "calculadora.h"

int main() {
    char expr[] = "8 + (5 * (2 + 4))";
    printf("%s\n", getFormaPosFixa(expr));
    return 0;
}
