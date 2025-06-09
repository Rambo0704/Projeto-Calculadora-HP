#include <stdio.h>
#include <stdlib.h> // Para a função atoi
#include <string.h> // Para a função strtok

int main() {
    // String original (é uma boa prática não usar um literal constante
    // pois strtok modifica a string)
    char str[] = "3 + 4 / 2";

    // 1. Obter o token como string (char *)
    char *token_string = strtok(str, " ");

    p

    return 0;
}