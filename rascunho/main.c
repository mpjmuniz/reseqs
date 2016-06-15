#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h> /* linkar com -lm*/

#define TAM_MAX 1024
/*Tamanho máximo da expressão aceita*/

/**
 *	TODO:
 *		- Implementar pilha para expressão
 *		- Implementar avaliação de expressão
 *		- Implementar polinômio
 *		
 */

void sair(const char *mensagem){
	if(errno){
		perror(mensagem);
	} else {
		printf("ERRO: %s\n", mensagem);
	}

	exit(EXIT_FAILURE);
}

typedef int (*compare_cb) (int a, int b);
typedef double (*double_valorado) (double arg);
	
void str_analisar(char *expr){
	if(!expr) sair("Expressão Inválida.");
	expr[TAM_MAX - 1] = '\0';

	char lido;
	int i = 0;

	for(i = 0; (lido = expr[i]) != '\0'; i++){
		printf("%c\n", lido);
		/* Fazer aqui a interpretação do caractere atual da expressão*/
		/* Implementar inserção na pilha*/
	}
}

int amain(int argc, char *argv[]){
	/*
	 *	Padrão Standard Argument:
	 *		- 0: programa
	 *		- 1: string com expressão da função
	 *		- 2: índice do método
	 *			- 0: posição falsa
	 *			- 1: bisseção
	 *			- 2: iterativo linear
	 *			- 3: newton raphson
	 *			- 4: secante
	 *		- 3: precisão
	 *		- 4: limite inferior do intervalo / valor inicial Xn
	 *		- 5: limite superior do intervalo / valor inicial Xn-1
	 * */

	if(argc > 1){
		//Implementar tratamento do stdarg
	} else {
		//Implementar tratamento da interface interativa
	}
	
	return 0;
}
