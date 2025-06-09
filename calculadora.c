#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <ctype.h>
#include <string.h> 


#define MAX_EXPR_SIZE 512
#define STACK_DEPTH 50 

typedef struct {
    char items[STACK_DEPTH][MAX_EXPR_SIZE]; 
    int top;
} Pilha_Caracter;


void initPilha_Caracter(Pilha_Caracter *s) {
    s->top = -1;
}


bool verificarPilha_Caracter(Pilha_Caracter *s) {
    return s->top == -1;
}


void InserirChar(Pilha_Caracter *s, const char* value) {
    if (s->top >= STACK_DEPTH - 1) {
        printf("Erro: Estouro da pilha de strings!\n");
        exit(1);
    }
    strcpy(s->items[++(s->top)], value);
}


void RetirarChar(Pilha_Caracter *s, char* dest) {
    if (verificarPilha_Caracter(s)) { 
        printf("Erro: Pilha de strings vazia!\n");
        exit(1);
    }
    strcpy(dest, s->items[(s->top)--]);
}



char *getFormaInFixa(char *Str) {
    Pilha_Caracter pilha;
    initPilha_Caracter(&pilha);
    
    
    static char finalResult[MAX_EXPR_SIZE];

    
    char strCopy[MAX_EXPR_SIZE];
    strcpy(strCopy, Str);

    char *token = strtok(strCopy, " ");
    
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
            char operando1[MAX_EXPR_SIZE];
            
            RetirarChar(&pilha, operando1);

            char novaExpr[MAX_EXPR_SIZE];
            sprintf(novaExpr, "%s(%s)", token, operando1);
            
            InserirChar(&pilha, novaExpr);
        }
        
        else
        {
            char operando2[MAX_EXPR_SIZE];
            char operando1[MAX_EXPR_SIZE];
            
            RetirarChar(&pilha, operando2);
            RetirarChar(&pilha, operando1);

            char novaExpr[MAX_EXPR_SIZE];
            sprintf(novaExpr, "(%s %s %s)", operando1, token, operando2);
           
            InserirChar(&pilha, novaExpr);
        }

        token = strtok(NULL, " ");
    }

    
    RetirarChar(&pilha, finalResult);
    return finalResult;
}