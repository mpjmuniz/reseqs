#include <metodos.h>

/*Método da Bisseção*/
Intervalo *bissecao(Funcao *f, Intervalo *i, double precisao){
	assert(f != NULL && "função inválida\n");
	assert(i != NULL && "Intervalo inválido\n");

	Intervalo *saida = intervalo(i->a, i->b);
	double m,
		   x;
	
	while(saida->b - saida->a >= precisao){
		m = funcao_avlr(f, saida->a);
		x = (saida->a + saida->b) / 2;

		if(m * funcao_avlr(f, x) > 0){
			saida->a = x;
		} else {
			saida->b = x;
		}
	}
	
	return saida;
}

/*Método da posição falsa*/
double posicao_falsa(Funcao *f, Intervalo *i, double precisao){
	assert(f != NULL && "função inválida\n");
	assert(i != NULL && "Intervalo inválido\n");

	double m,
		   x,
		   valor_b;
	if(fabs(funcao_avlr(f, i->a)) < precisao) return i->a;
	if(fabs(funcao_avlr(f, i->b)) < precisao) return i->b;

	Intervalo *aux = intervalo(i->a, i->b);

	while(aux->b - aux->a >= precisao){
		m = funcao_avlr(f, aux->a);
		valor_b = funcao_avlr(f, aux->b);
		
		x = (aux->a * valor_b - aux->b * m) / (valor_b - m);
		if(fabs(funcao_avlr(f, x)) < precisao){
			intervalo_lbr(aux);
			return x;
		}

		if(m * funcao_avlr(f, x) > 0){
			aux->a = x;
		} else {
			aux->b = x;
		}
	}
	intervalo_lbr(aux);
	return (double) ((aux->a + aux->b) / 2);
}

/*Método Iterativo Linear*/
double iterativo_linear(Funcao *f, Funcao *iteracao, double inicial, double precisao){
	assert(f != NULL && "Função principal inválida\n");
	assert(iteracao != NULL && "Função de iteração inválida\n");
	if(fabs(funcao_avlr(f, inicial)) < precisao){
		return inicial;
	}
	double x = INT_MAX, x_ant = inicial;
	while(fabs(funcao_avlr(f, x_ant)) >= precisao && fabs(x - x_ant) >= precisao){
		x = funcao_avlr(iteracao, x_ant);
		x_ant = x;
	}

	return x;
}

/*Método de Newton-Raphson*/
double newton_raphson(Funcao *f, Funcao *derivada, double inicial, double precisao){
	assert(f != NULL && "Função principal inválida\n");
	assert(derivada != NULL && "Função de iteração inválida\n");
	
	if(fabs(funcao_avlr(f, inicial)) <= precisao) return inicial;

	double x = 0, x_ant = inicial;
	do{
		x = x_ant - (funcao_avlr(f, x_ant) / funcao_avlr(derivada, x_ant));
		x_ant = x;
	} while(fabs(funcao_avlr(f, x)) >= precisao && fabs(x - x_ant) >= precisao);
	
	return x;
}

/*Método da Secante*/
double secante(Funcao *f, double inicial1, double inicial2, double precisao){
	assert(f != NULL && "Função Inválida\n");
	if(fabs(funcao_avlr(f, inicial1)) < precisao) return inicial1;
	if(fabs(funcao_avlr(f, inicial2)) < precisao || fabs(inicial2 - inicial1)) return inicial1;
	
	double x_ant1 = inicial2, x_ant2 = inicial1, x;
	do{
		x = x_ant1 - (funcao_avlr(f, x_ant1) * (x_ant1 - x_ant2)) / (funcao_avlr(f, x_ant1) - funcao_avlr(f, x_ant2));
		x_ant2 = x_ant1;
		x_ant1 = x;
	} while(fabs(funcao_avlr(f, x)) >= precisao && fabs(x - x_ant1) >= precisao);
	
	return x;
}
