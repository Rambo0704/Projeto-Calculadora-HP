#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "calculadora.h"

int main() {
    char expr[] = "(3 + 4) * 5";
    printf("%s\n", getFormaPosFixa(expr));
    return 0;
}
