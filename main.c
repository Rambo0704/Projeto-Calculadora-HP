#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "calculadora.h"

int main() {
    Expressao finalResult;

    char *posFixaGerada = getFormaPosFixa("sen(45) ^2 + 0.5");
    printf("Pós-fixa gerada: %s\n", posFixaGerada);
    
    char *inFixaGerada = getFormaInFixa("0.5 45 sen 2 ^ +");
    printf("In-fixa da string dada: %s\n", inFixaGerada);
    
    finalResult.Valor = getValorPosFixa("0.5 45 sen 2 ^ +");
    printf("Valor da expressã pos fix: %.2f\n", finalResult.Valor);
    
    float valorInFixa = getValorInFixa("sen(45) ^2 + 0,5");
    printf("Valor da expressão in-fixa: %.2f\n", valorInFixa);
    return 0;
}
