#ifndef __arvore_h__
#define __arvore_h__

#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <float.h>

#include <funcoes.h>

#define TAM 1024

/*Ponteiros de funções auxiliares*/
typedef double (* func) (double entrada);
typedef double (* operador) (double operando1, double operando2);

/*Árvore de Avaliação. Folhas são pilhas de expressões*/
struct arvore{
	/*expressão pode ser
	 * - função (tipo 0)
	 * - operador (tipo 1)
	 * - operando (tipo 2: escalar, tipo 3: variavel)
	 * - parêntese (tipo 4) TODO: apagar este
	 *   */
	void *expressao;
	struct arvore *direita;
	struct arvore *esquerda;
	/*para expressões compostas*/
	struct arvore *dentro;
	int tipo;
};
typedef struct arvore Arvore;

/*	Gerar árvore de expressões à partir da expressão @expr*/
Arvore *gerar(char *expr);

/*Avalia a expressão descrita por @arvr em x = @ponto*/
double arvore_avlr(Arvore *arvr, double ponto);

/*	Liberar árvore de expressões*/
void arvore_lbr(Arvore *arvr);
#endif
