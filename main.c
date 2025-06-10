#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "calculadora.h"

int main() {
    char expr[] = "(45 + 60) * cos(30)";
    printf("%s\n", getFormaPosFixa(expr));
    return 0;
}
