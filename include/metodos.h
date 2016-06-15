#ifndef __metodos_h__
#define __metodos_h__

#include <math_util.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

/*Método da Bisseção*/
Intervalo *bissecao(Funcao *f, Intervalo *i, double precisao);

/*Método da posição falsa*/
double posicao_falsa(Funcao *f, Intervalo *i, double precisao);

/*Método Iterativo Linear*/
double iterativo_linear(Funcao *f, Funcao *iteracao, double inicial, double precisao);

/*Método de Newton-Raphson*/
double newton_raphson(Funcao *f, Funcao *derivada, double inicial, double precisao);

/*Método da Secante*/
double secante(Funcao *f, double inicial1, double inicial2, double precisao);

#endif
