#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <ctype.h>
#include <string.h> 
#include "calculadora.h"

#define max_express 512
#define max_itens 50 
typedef struct {
    char items[max_itens][max_express]; 
    int top;
} Pilha_Caracter;
void CriarPilha_Caracter(Pilha_Caracter *s) {
    s->top = -1;
}
void InserirChar(Pilha_Caracter *s, const char* value) {
    if (s->top >= max_itens - 1) {
        printf("Erro: Estouro da pilha de strings!\n");
        exit(1);
    }
    strcpy(s->items[++(s->top)], value);
}

void RetirarChar(Pilha_Caracter *s, char* value) {
    strcpy(value, s->items[(s->top)--]);
}

char* getFormaInFixa(char *Str) {
    Pilha_Caracter pilha;
    CriarPilha_Caracter(&pilha);
    
    static Expressao finalResult;

    char copia[max_express];
    strcpy(copia, Str);

    char *token = strtok(copia, " ");
    
    while (token != NULL) {
        if (strcmp(token, "+") != 0 && strcmp(token, "-") != 0 &&
            strcmp(token, "*") != 0 && strcmp(token, "/") != 0 &&
            strcmp(token, "%") != 0 && strcmp(token, "^") != 0 &&
            strcmp(token, "sen") != 0 && strcmp(token, "cos") != 0 &&
            strcmp(token, "tg") != 0 && strcmp(token, "log") != 0 &&
            strcmp(token, "raiz") != 0) 
        {
            InserirChar(&pilha, token);
        }
        else if (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 ||
                 strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 ||
                 strcmp(token, "log") == 0) 
        {
            char operando1[max_express];
            RetirarChar(&pilha, operando1);

            char novaExpr[max_express];
            sprintf(novaExpr, "%s(%s)", token, operando1);
            InserirChar(&pilha, novaExpr);
        } 
        else 
        {
            char operando2[max_express];
            char operando1[max_express];
            RetirarChar(&pilha, operando2);
            RetirarChar(&pilha, operando1);

            char novaExpr[max_express];
            sprintf(novaExpr, "(%s %s %s)", operando1, token, operando2);
            InserirChar(&pilha, novaExpr);
        }

        token = strtok(NULL, " ");
    }

    RetirarChar(&pilha, finalResult.inFixa);
    return finalResult.inFixa;
}

