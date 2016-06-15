#include "minunit.h"
#include <math_util.h>
#include <funcoes.h>
#include <arvore.h>
#include <assert.h>

static Funcao *f = NULL;

double res;

char *test_x(){
	f = funcao("x");
	mu_assert(f != NULL, "Falha na criação.");

	res = funcao_avlr(f, 4);
	mu_assert(res == 4, "Erro na avaliação.");

	funcao_lbr(f);

	return NULL;
}

char *test_cte(){
	f = funcao("5");
	mu_assert(f != NULL, "Falha na criação.");

	res = funcao_avlr(f, 4);
	mu_assert(res == 5, "Erro na avaliação. ");

	funcao_lbr(f);

	return NULL;
}

char *test_soma(){
	f = funcao("x+1");
	mu_assert(f != NULL, "Falha na criação.");

	res = funcao_avlr(f, 4);
	mu_assert(res == 5, "Erro na avaliação.");

	funcao_lbr(f);

	return NULL;
}

char *test_subtracao(){
	f = funcao("x-4");
	mu_assert(f != NULL, "Falha na criação.");

	res = funcao_avlr(f, 3);
	mu_assert(res == -1, "Erro na avaliação.");

	funcao_lbr(f);

	return NULL;
}

char *test_composicao(){
	f = funcao("x^2-5*x+4");
	mu_assert(f != NULL, "Falha na criação.");

	res = funcao_avlr(f, 2);
	mu_assert(res == -2, "Erro na avaliação.");

	funcao_lbr(f);

	return NULL;
}

char *test_cosseno(){
	f = funcao("cos(x)");
	mu_assert(f != NULL, "Falha na criação.");

	res = funcao_avlr(f, 0);
	mu_assert(res == 1, "Erro na avaliação.");

	funcao_lbr(f);

	return NULL;
}

char *all_tests(){
	mu_suite_start();
	
	mu_run_test(test_x);
	mu_run_test(test_cte);
	mu_run_test(test_soma);
	mu_run_test(test_subtracao);
	mu_run_test(test_composicao);
	mu_run_test(test_cosseno);


	return NULL;
}

RUN_TESTS(all_tests);

