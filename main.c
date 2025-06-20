#include <stdio.h>
#include <string.h>
#include "expressão.h"

int main() {
    char *expPosfixas[] = { //guardamos as expressões do teste do documento na forma pos-fixa
        "3 4 + 5 *",
        "7 2 * 4 +",
        "8 5 2 4 + * +",
        "6 2 / 3 + 4 *",
        "9 5 2 8 * 4 + * +",
        "2 3 + log 5 /",
        "10 log 3 * 2 +",
        "45 60 + 30 cos *",
        "0.5 45 sen 2 ^ +"
    };

    char *expInfixas[] = { //guardamos as expressões do teste do documento na forma in-fixa
        "(3 + 4) * 5",
        "7 * 2 + 4",
        "8 + (5 * (2 + 4))",
        "(6 / 2 + 3) * 4",
        "9 + (5 * (2 * 8 + 4))",
        "log(2 + 3) / 5",
        "(log(10) * 3) + 2",
        "(45 + 60) * cos(30)",
        "sen(45) ^ 2 + 0.5"
    };

    int n = 9;

    for (int i = 0; i < n; i++) {
        Expressao e;
        strcpy(e.posFixa, expPosfixas[i]);
        strcpy(e.inFixa, getFormaInFixa(e.posFixa));
        e.Valor = getValorPosFixa(e.posFixa);
        printf("Teste %d\n", i + 1);
        printf("  Entrada Pos-fixa: %s\n", e.posFixa);
        printf("  In-fixa gerada:   %s\n", e.inFixa);
        printf("  Valor calculado:  %.4f\n", e.Valor);
        Expressao Einfixa;
        strcpy(Einfixa.inFixa, expInfixas[i]);
        strcpy(Einfixa.posFixa, getFormaPosFixa(Einfixa.inFixa));
        Einfixa.Valor = getValorInFixa(Einfixa.inFixa);
        printf("  Entrada In-fixa:  %s\n", Einfixa.inFixa);
        printf("  Pos-fixa gerada:  %s\n", Einfixa.posFixa);
        printf("  Valor calculado:  %.4f\n", Einfixa.Valor);
        printf("--------------------------------------------------\n");
    }
    return 0;
}
