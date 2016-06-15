#include <math_util.h>

Intervalo *intervalo(double a, double b){
	Intervalo *i = (Intervalo *) malloc(sizeof(Intervalo));
	i->a = a;
	i->b = b;
	return i;
}

void intervalo_lbr(Intervalo *i){
	if(i == NULL) return;
	free(i);
}

double funcao_avlr(Funcao *f, double ponto){
	assert(f != NULL && "Função inválida\n");

	return arvore_avlr(f->avaliacao, ponto);
}

Funcao *funcao(char *expressao){
	assert(expressao != NULL && "Expressão Inválida, impossível criar função.\n");

	Funcao *f = (Funcao *) malloc(sizeof(Funcao));
	f->expressao = (char *) malloc(TAM);
	assert(f != NULL && "Falta de memória.\n");
	
	f->expressao = strncpy(f->expressao, expressao, TAM);
	f->avaliacao = gerar(f->expressao);
	
	return f;
}

void funcao_lbr(Funcao *f){
	if(f == NULL) return;
	if(f->expressao != NULL) free(f->expressao);
	arvore_lbr(f->avaliacao);
	free(f);
}
