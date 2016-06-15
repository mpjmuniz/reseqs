#include <funcoes.h>

double identidade(double x){
	return x;
}

double soma(double x, double y){
	return x + y;
}

double subtracao(double x, double y){
	return x - y;
}

double multiplicacao(double x, double y){
	return x * y;
}

double divisao(double x, double y){
	assert(y != 0 && "Divisão por 0.\n");
	return x / y;
}

double resto(double x, double y){
	assert(y != 0 && "Divisão por 0.\n");
	return (int) x % (int) y;
}
