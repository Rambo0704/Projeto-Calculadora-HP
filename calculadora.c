#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <ctype.h>
#include <string.h> 
#include "calculadora.h"

#define max_express 512
#define max_itens 50
typedef struct 
{
    char expressao[max_express];
} Item;
typedef struct {
    Item items[max_itens];
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
    strcpy(s->items[++(s->top)].expressao, value);
}

void RetirarChar(Pilha_Caracter *s, char* value) {
    strcpy(value, s->items[(s->top)--].expressao);
}

int prioridade(const char* op) {
    if (strcmp(op, "^") == 0) return 4;
    if (strcmp(op, "*") == 0 || strcmp(op, "/" ) == 0 || strcmp(op, "%") == 0) return 3;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 2;
    return 0;
}
bool associativoADireita(const char* op) {
    return (strcmp(op, "^") == 0);
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
char *getFormaPosFixa(char *Str) {
    Pilha_Caracter operadores;
    CriarPilha_Caracter(&operadores);

    static Expressao finalResult;
    finalResult.posFixa[0] = '\0'; // Limpa o resultado anterior

    char copia[max_express];
    strncpy(copia, Str, max_express - 1);
    copia[max_express - 1] = '\0';

    char *token = strtok(copia, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (strlen(token) > 1 && isdigit(token[1])) || isalpha(token[0])) {
            strcat(finalResult.posFixa, token);
            strcat(finalResult.posFixa, " ");
        } 
        else if (strcmp(token, "(") == 0) {
            InserirChar(&operadores, token);
        } 
        else if (strcmp(token, ")") == 0) {
            char op[max_express];
            RetirarChar(&operadores, op);
            while (strcmp(op, "(") != 0) {
                strcat(finalResult.posFixa, op);
                strcat(finalResult.posFixa, " ");
                RetirarChar(&operadores, op);
            }
        } 
        else { // Se for um operador
            while (operadores.top >= 0) {
                char topo[max_express];
                strcpy(topo, operadores.items[operadores.top].expressao);
                if ((prioridade(topo) >= prioridade(token)) && !associativoADireita(token)) {
                    char op[max_express];
                    RetirarChar(&operadores, op);
                    strcat(finalResult.posFixa, op);
                    strcat(finalResult.posFixa, " ");
                } else {
                    break;
                }
            }
            InserirChar(&operadores, token);
        }
        token = strtok(NULL, " ");
    }
    while (operadores.top >= 0) {
        char op[max_express];
        RetirarChar(&operadores, op);
        strcat(finalResult.posFixa, op);
        strcat(finalResult.posFixa, " ");
    }
    return finalResult.posFixa;
}
