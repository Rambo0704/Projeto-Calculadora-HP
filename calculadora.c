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
char* getFormaPosFixa(char *Str) {
    static Expressao finalResult;
    finalResult.inFixa[0] = '\0';
    Pilha_Caracter operadores;
    CriarPilha_Caracter(&operadores);

    char copia[max_express];
    strcpy(copia, Str);
    char *token = strtok(copia, " ");

    while (token != NULL) {
        char c = token[0];
        if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            strcat(finalResult.inFixa, token);
            strcat(finalResult.inFixa, " ");
        } else {
            int prec;
            if (strcmp(token, "^") == 0) {
                prec = 3;
            } else if (strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || strcmp(token, "%") == 0) {
                prec = 2;
            } else {
                prec = 1; 
            }
            while (operadores.top >= 0) {
                char topo[max_express];
                strcpy(topo, operadores.items[operadores.top].expressao);

                int precTopo;
                if (strcmp(topo, "^") == 0) {
                    precTopo = 3;
                } else if (strcmp(topo, "*") == 0 || strcmp(topo, "/" ) == 0 || strcmp(topo, "%" ) == 0) {
                    precTopo = 2;
                } else if (strcmp(topo, "+") == 0 || strcmp(topo, "-") == 0) {
                    precTopo = 1;
                } else {
                    precTopo = 0;
                }

                if (precTopo >= prec) {
                    RetirarChar(&operadores, topo);
                    strcat(finalResult.inFixa, topo);
                    strcat(finalResult.inFixa, " ");
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
        strcat(finalResult.inFixa, op);
        strcat(finalResult.inFixa, " ");
    }
    return finalResult.inFixa;
}
