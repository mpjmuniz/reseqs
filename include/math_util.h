#ifndef __math_util_h__
#define __math_util_h__

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include <funcoes.h>
#include <arvore.h>

#define TAM 1024

/*Definição de Intervalo*/

struct intervalo{
	double a; // Início
	double b; // Fim
};
typedef struct intervalo Intervalo;

/*definir intervalo de limite superior @lim-sup e limite inferior @lim-inf*/
Intervalo *intervalo(double lim_inf, double lim_sup);

/*Liberar Intervalo*/
void intervalo_lbr(Intervalo *i);

/*Definição de funcao*/

struct funcao{
	char *expressao;
	Arvore *avaliacao;
};
typedef struct funcao Funcao;

/* Avaliar valor da função @f em x = @ponto*/
double funcao_avlr(Funcao *f, double ponto);

/* Criar função com @expressão*/
Funcao *funcao(char *expressao);

/*Liberar Funcao*/
void funcao_lbr(Funcao *f);

#endif
