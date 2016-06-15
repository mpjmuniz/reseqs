#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math_util.h>
#include <metodos.h>
/*
 *	Métodos: 
 *		0 : Método da Bisseção
 *		1 : Método da Posição Falsa
 *		2 : Método Iterativo Linear
 *		3 : Método de Newton Raphson
 *		4 :	Método da Secante
 *
 * */

int main(int argc, char **argv){
	int metodo = -1;
	double precisao = 0,
		   retorno = 0,
		   limite_inf = 0,
		   limite_sup = 0,
		   aprox_inicial = 0,
		   aprox_inicial2 = 0;
			
	Funcao *f = NULL, *aux = NULL;
	Intervalo *interv = NULL, *saida = NULL;

	/*	$ interface <metodo> <funcao> <precisao> <...>*/
	if(argc == 6){
		metodo = atoi(argv[1]);
		f = funcao(argv[2]);
		precisao = atof(argv[3]);

		if(metodo == 0 || metodo == 1){
			/* Se for bisseção ou posição falsa 
			 * <...> <limite-inferior-intervalo> <limite-superior-intervalo>*/
			limite_inf = atof(argv[4]);
			limite_sup = atof(argv[5]);
		} else if(metodo == 2|| metodo == 3){
			/* Se for iterativo-linear ou newton raphson
			 * <...> <derivada/funcao-iterativa> <aprox-inicial> */
			aux = funcao(argv[4]);
			aprox_inicial = atof(argv[5]);
		} else if(metodo == 4){
			/* Se for secante 
			 * <...> <aprox-inicial0> <aprox-inicial1> */
			aprox_inicial = atof(argv[4]);
			aprox_inicial2 = atof(argv[5]);
		} else {
			printf("\n--------------------\nErro de uso:\n");
			printf("Em uma linha: \n");
			printf("$ interface <metodo(0, ..., 4)> <funcao(x^2-3*x+arctan(x))> <precisao(0.00003)> <...>\n");
			printf("0. Bisseção, 1. Posicao Falsa: <...> = <limite-inferior-intervalo(4.5)> <limite-superior-intervalo(5.10)> \n");
			printf("2. Iterativo Linear, 3. Newton Raphson: <...> = <derivada/funcao-iterativa(2*x-3+1/(1+x^2))> <aprox-inicial(3.23)> \n");
			printf("4. Secante: <...> = <aprox-inicial0(3.23)> <aprox-inicial1(4.323)> \n");
		}
	} else {
		char expr[1024];
		int rc;

		printf("Resolução Numérica das raízes de Equações de uma variável Real\n");
		printf("Escolha o seu método:\n");
		printf("\t0. Método da Bisseção\n");
		printf("\t1. Método da Posição Falsa\n");
		printf("\t2. Método Iterativo-Linear\n");
		printf("\t3. Método de Newton-Raphson\n");
		printf("\t4. Método da Secante\n");
		
		rc = scanf("%d", &metodo);
		if(rc != 1 || metodo < 0 || metodo >= 5) printf("Método inválido. Digite o índice do método que você prefere.\n");

		printf("Digite a sua função. lembre-se de colocar todos os parênteses!\n");
		rc = scanf("%s", expr);
		assert(rc == 1 && "Função Inválida.\n");
		expr[1023] = '\0';
		f = funcao(expr);

		printf("Digite a sua precisao.\n");
		rc = scanf("%lf", &precisao);
		assert(rc == 1 && "Precisao inválida. indique um numero em ponto flutuante.\n");

		if(metodo == 0 || metodo == 1){
			printf("Digite os limites inferior e superior, respectivamente, como valores em pto. flutuante:\n");
			rc = scanf("%lf %lf", &limite_inf, &limite_sup);
			assert(rc == 2 && "Limites inválidos.\n");
		} else if(metodo == 2 || metodo == 3){
			
			if(metodo == 2){
				printf("Digite a função iteradora:\n");
			} else {
				printf("Digite a derivada da função dada:\n");
			}

			rc = scanf("%s", expr);
			aux = funcao(expr);
			assert(rc == 1 && aux != NULL && "Função inválida.\n");

			printf("Digite a aproximação inicial:\n");
			rc = scanf("%lf", &aprox_inicial);
			assert(rc == 1 && "Aproximação inicial inválida.\n");
		} else if(metodo == 4){
			printf("Digite as aproximações inicials, em pto. flutuante:\n");
			rc = scanf("%lf %lf", &aprox_inicial, &aprox_inicial2);
			assert(rc == 2 && "Aproximações iniciais inválidas.\n");
		} else {
			assert(metodo >= -1 && metodo < 5 && "Método Inválido.\n");
		}
	}

	switch(metodo){
		case 0:
			interv = intervalo(limite_inf, limite_sup);
			saida = bissecao(f, interv, precisao);
			printf("Intervalo que contém a raiz: [%f;%f]\n", saida->a, saida->b);
			break;
		case 1:
			interv = intervalo(limite_inf, limite_sup);
			retorno = posicao_falsa(f, interv, precisao);
			printf("Resultado: %f\n", retorno);
			break;
		case 2:
			retorno = iterativo_linear(f, aux, aprox_inicial, precisao);
			printf("Resultado: %f\n", retorno);
			break;
		case 3:
			retorno = newton_raphson(f, aux, aprox_inicial, precisao);
			printf("Resultado: %f\n", retorno);
			break;
		case 4:
			retorno = secante(f, aprox_inicial, aprox_inicial2, precisao);
			printf("Resultado: %f\n", retorno);
			break;
		default:
			assert(metodo > 1 && metodo < 5 && "Método inválido\n");
			break;
	}

	funcao_lbr(f);
	funcao_lbr(aux);
	intervalo_lbr(interv);
	intervalo_lbr(saida);

	return 0;
}
