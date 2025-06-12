#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <ctype.h>
#include <string.h> 
#include "calculadora.h"

#define max_express 512
#define max_itens 50

typedef struct {
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

char *getFormaPosFixa(char *Str) {
    Pilha_Caracter operadores;
    CriarPilha_Caracter(&operadores);

    static Expressao finalResult;
    finalResult.posFixa[0] = '\0';

    char token[max_express];
    int i = 0, j = 0;

    while (Str[i] != '\0') {
        if (isspace(Str[i])) {
            i++;
            continue;
        }
        //número ou variável 
        if (isdigit(Str[i]) || isalpha(Str[i])) {
            j = 0;
            while (isdigit(Str[i]) || isalpha(Str[i])) {
                token[j++] = Str[i++];
            }
            token[j] = '\0';
            strcat(finalResult.posFixa, token);
            strcat(finalResult.posFixa, " ");
        }
        //parêntese esquerdo
        else if (Str[i] == '(') {
            InserirChar(&operadores, "(");
            i++;
        }

        //parêntese direito
        else if (Str[i] == ')') {
            char op[max_express];
            RetirarChar(&operadores, op);
            while (strcmp(op, "(") != 0) {
                strcat(finalResult.posFixa, op);
                strcat(finalResult.posFixa, " ");
                RetirarChar(&operadores, op);
            }
            i++;
        }

        //operador
        else {
            char op1[2] = {Str[i], '\0'};

            while (operadores.top >= 0) {
                char topo[max_express];
                strcpy(topo, operadores.items[operadores.top].expressao);

                int p_topo = 0, p_token = 0;
                if (strcmp(topo, "^") == 0) p_topo = 4;
                else if (strcmp(topo, "*") == 0 || strcmp(topo, "/") == 0 || strcmp(topo, "%") == 0) p_topo = 3;
                else if (strcmp(topo, "+") == 0 || strcmp(topo, "-") == 0) p_topo = 2;

                if (strcmp(op1, "^") == 0) p_token = 4;
                else if (strcmp(op1, "*") == 0 || strcmp(op1, "/") == 0 || strcmp(op1, "%") == 0) p_token = 3;
                else if (strcmp(op1, "+") == 0 || strcmp(op1, "-") == 0) p_token = 2;

                bool direita = (strcmp(op1, "^") == 0);

                if ((p_topo >= p_token) && !direita) {
                    char op[max_express];
                    RetirarChar(&operadores, op);
                    strcat(finalResult.posFixa, op);
                    strcat(finalResult.posFixa, " ");
                } else {
                    break;
                }
            }
            InserirChar(&operadores, op1);
            i++;
        }
    }

    while (operadores.top >= 0) {
        char op[max_express];
        RetirarChar(&operadores, op);
        strcat(finalResult.posFixa, op);
        strcat(finalResult.posFixa, " ");
    }

    return finalResult.posFixa;
}
