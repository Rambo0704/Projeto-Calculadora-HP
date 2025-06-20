#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h> //apos ler a documentalção, percebi que a biblioteca ctype.h é necessária para usar funções como isspace, isalpha, isdigit, etc.
#include <string.h>
#include <math.h>

#define max_express 512
#define max_itens 50
#define max_float_itens 100
#define M_PI 3.14159265358979323846

typedef struct {
    char inFixa[max_express];
    char posFixa[max_express];
    float Valor;
} Expressao;

typedef struct {
    char expressao[max_express];
} Item_Caracter;

typedef struct {
    Item_Caracter items[max_itens];
    int top;
} Pilha_Caracter;

typedef struct {
    float items[max_float_itens];
    int top;
} Pilha_Float;

void CriarPilha_Caracter(Pilha_Caracter *s) {
    s->top = -1;
}

void InserirChar(Pilha_Caracter *s, const char* value) {
    if (s->top >= max_itens - 1) exit(1);
    strcpy(s->items[++(s->top)].expressao, value);
}

void RetirarChar(Pilha_Caracter *s, char* value) {
    strcpy(value, s->items[(s->top)--].expressao);
}

void CriarPilha_Float(Pilha_Float *p) {
    p->top = -1;
}

void Empilhar(Pilha_Float *p, float val) {
    if (p->top >= max_float_itens - 1) exit(1);
    p->items[++(p->top)] = val;
}

float Desempilhar(Pilha_Float *p) {
    if (p->top < 0) exit(1);
    return p->items[(p->top)--];
}

char* getFormaInFixa(char *Str) {
    Pilha_Caracter pilha;
    CriarPilha_Caracter(&pilha);

    static Expressao finalResult;
    char copia[max_express];
    strcpy(copia, Str);
    char *token = strtok(copia, " ");

    while (token != NULL) {
        if (strcmp(token, "+") && strcmp(token, "-") &&
            strcmp(token, "*") && strcmp(token, "/") &&
            strcmp(token, "%") && strcmp(token, "^") &&
            strcmp(token, "sen") && strcmp(token, "cos") &&
            strcmp(token, "tg") && strcmp(token, "log") &&
            strcmp(token, "raiz")) {
            InserirChar(&pilha, token);
        } else if (!strcmp(token, "raiz") || !strcmp(token, "sen") ||
                   !strcmp(token, "cos") || !strcmp(token, "tg") ||
                   !strcmp(token, "log")) {
            char operando1[max_express];
            RetirarChar(&pilha, operando1);
            char novaExpr[max_express];
            sprintf(novaExpr, "%s(%s)", token, operando1);
            InserirChar(&pilha, novaExpr);
        } else {
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

        if (isalpha(Str[i])) {
            j = 0;
            while (isalpha(Str[i])) {
                token[j++] = Str[i++];
            }
            token[j] = '\0';
            InserirChar(&operadores, token);
        }
        else if (isdigit(Str[i]) || (Str[i] == '.' && isdigit(Str[i + 1]))) {
            j = 0;
            while (isdigit(Str[i]) || Str[i] == '.') {
                token[j++] = Str[i++];
            }
            token[j] = '\0';
            strcat(finalResult.posFixa, token);
            strcat(finalResult.posFixa, " ");
        }
        else if (Str[i] == '(') {
            InserirChar(&operadores, "(");
            i++;
        }
        else if (Str[i] == ')') {
            char op[max_express];
            RetirarChar(&operadores, op);
            while (strcmp(op, "(") != 0) {
                strcat(finalResult.posFixa, op);
                strcat(finalResult.posFixa, " ");
                RetirarChar(&operadores, op);
            }
            if (operadores.top >= 0) {
                strcpy(op, operadores.items[operadores.top].expressao);
                if (strcmp(op, "sen") == 0 || strcmp(op, "cos") == 0 ||
                    strcmp(op, "tg") == 0 || strcmp(op, "log") == 0 ||
                    strcmp(op, "raiz") == 0) {
                    RetirarChar(&operadores, op);
                    strcat(finalResult.posFixa, op);
                    strcat(finalResult.posFixa, " ");
                }
            }
            i++;
        }
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
                } else break;
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

float getValorPosFixa(char *StrPosFixa) {
    Pilha_Float pilha;
    CriarPilha_Float(&pilha);
    char copia[max_express];
    strcpy(copia, StrPosFixa);
    char *token = strtok(copia, " ");
    while (token != NULL) {
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
            strcmp(token, "%") == 0 || strcmp(token, "^") == 0) {
            float b = Desempilhar(&pilha);
            float a = Desempilhar(&pilha);
            float res = 0;
            if (strcmp(token, "+") == 0) res = a + b;
            else if (strcmp(token, "-") == 0) res = a - b;
            else if (strcmp(token, "*") == 0) res = a * b;
            else if (strcmp(token, "/") == 0) res = a / b;
            else if (strcmp(token, "%") == 0) res = fmod(a, b);
            else if (strcmp(token, "^") == 0) res = pow(a, b);
            Empilhar(&pilha, res);
        } else if (strcmp(token, "log") == 0 || strcmp(token, "sen") == 0 ||
                   strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 ||
                   strcmp(token, "raiz") == 0) {
            float a = Desempilhar(&pilha);
            float res = 0;
            if (strcmp(token, "log") == 0) res = log10(a);
            else if (strcmp(token, "raiz") == 0) res = sqrt(a);
            else if (strcmp(token, "sen") == 0) res = sin(a * M_PI / 180);
            else if (strcmp(token, "cos") == 0) res = cos(a * M_PI / 180);
            else if (strcmp(token, "tg") == 0) res = tan(a * M_PI / 180);
            Empilhar(&pilha, res);
        } else {
            Empilhar(&pilha, atof(token));
        }
        token = strtok(NULL, " ");
    }
    return Desempilhar(&pilha);
}

float getValorInFixa(char *StrInFixa) {
    return getValorPosFixa(getFormaPosFixa(StrInFixa));
}
