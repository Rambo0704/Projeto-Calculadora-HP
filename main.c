#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <ctype.h>
#include <string.h> 
#include "calculadora.h"

int main(){
    char *result = getFormaInFixa("7 2 * 4 +");
    printf("Expressao em forma infixa: %s\n", result);

    return 0;
}
