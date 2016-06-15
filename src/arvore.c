#include <arvore.h>

/*TODO: Implementar:
 * 	- Avaliação da árvore
 * 	*/

/*
 *	expr : Expressão
 *	dir : Direita
 *	esq : Esquerda
 *	den : Dentro
 * */
Arvore *criar_subarvore(void *expr, int tipo, Arvore *dir, Arvore *esq, Arvore *den){
	assert(expr != NULL && "Expressão inválida.\n");

	Arvore *sub_arvore = (Arvore *) malloc(sizeof(Arvore));
	assert(sub_arvore != NULL && "Sub árvore inválida");
	
	sub_arvore->expressao = expr;
	sub_arvore->direita = dir;
	sub_arvore->esquerda = esq;
	sub_arvore->dentro = den;
	sub_arvore->tipo = tipo;

	return sub_arvore;
}

static void encaixar_arvore(Arvore **raiz, Arvore *composicao, Arvore *operador, Arvore *ramo){
	/*Se não é uma composição de função*/
	if(composicao == NULL){
		/*Se é uma expressão dentro de outra*/
		if(operador == NULL){
			*raiz = ramo;
		} else {
			(*raiz)->esquerda = ramo;
		}
	} else {
		if(operador == NULL){
			(*raiz)->dentro = ramo;
		} else{
			(*raiz)->dentro->esquerda = ramo;
		}
	}
}

static int procurar(char *onde, char *oque){
	char *saida = strstr(onde, oque);
	return saida != NULL;
}

/*	Gerar árvore de expressões à partir da expressão @expr*/
Arvore *gerar(char *expr){
	assert(expr != NULL && "Expressão inválida.\n");
	
	Arvore *arv = (Arvore *) malloc(sizeof(Arvore)),
		   *sub_arv = NULL,
		   *arv_composicao = NULL,
		   *arv_operador = NULL;

	char atual, 
		 atual_interno,
		 expressao_atual[TAM];

	int i = 0,
		j = 0,
		k = 0,
		poss_neg = 1, //flag para possibilidade de números negativos
		negativo = 0; //flag para avaliação de números negativos

	double *valor = NULL;

	while((atual = expr[i++]) != '\0'){

		if(atual == ' ' || atual == ')') continue;
		
		else if(atual == '('){

			//Expressão seguinte será uma sub árvore à direita 
			poss_neg = 1;
			continue;
			//Continue obrigatório, por causa do poss_neg

		} else if(atual == 'x'){

			 //Se é a variável, devo deixá-la para o tempo de avaliação 
			sub_arv = criar_subarvore(identidade, 3, NULL, NULL, NULL);
			arv_composicao = NULL;
			
			encaixar_arvore((arv_operador != NULL && arv_operador->esquerda == NULL) ? &arv_operador : &arv,
					arv_composicao, arv_operador, sub_arv);

		} else if(atual == '+'){

			arv_operador = criar_subarvore(soma, 1, arv, NULL, NULL);
			arv = arv_operador;

		} else if(atual == '-'){

			if(poss_neg == 1){
				negativo = 1;
			} else {
				arv_operador = criar_subarvore(subtracao, 1, arv, NULL, NULL);
				arv = arv_operador;
			}

		} else if(atual == '*'){

			if(arv_operador == NULL){
				arv_operador = criar_subarvore(multiplicacao, 1, arv, NULL, NULL);
				arv = arv_operador;
			} else {
				arv_operador->esquerda = criar_subarvore(multiplicacao, 1, arv_operador->esquerda, NULL, NULL);
				arv_operador = arv_operador->esquerda;
			}

		} else if(atual == '/'){

			if(arv_operador == NULL){
				arv_operador = criar_subarvore(divisao, 1, arv, NULL, NULL);
				arv = arv_operador;
			} else {
				arv_operador->esquerda = criar_subarvore(divisao, 1, arv_operador->esquerda, NULL, NULL);
				arv_operador = arv_operador->esquerda;
			}

		} else if(atual == '%'){
			
			arv_operador = criar_subarvore(resto, 1, arv, NULL, NULL);
			arv = arv_operador;

		} else if(atual == '^'){
			
			if(arv_operador == NULL){
				arv_operador = criar_subarvore(pow, 1, arv, NULL, NULL);
				arv = arv_operador;
			} else {
				arv_operador->esquerda = criar_subarvore(pow, 1, arv_operador->esquerda, NULL, NULL);
				arv_operador = arv_operador->esquerda;
			}

		} else if(isdigit(atual)){
			//Se é um dígito, pegar os outros 
			valor = (double *) malloc(sizeof(double));
			j = i;
			k = 0;

			expressao_atual[k++] = atual;
			
			while(((atual_interno = expr[j++]) != '\0') &&
					(isdigit(atual_interno) || atual_interno == ',' ||
					 atual_interno == '.')){

				expressao_atual[k++] = atual_interno;
			}

			expressao_atual[k] = '\0';
			
			i = j - 1;
			
			*valor = atof(expressao_atual);
			if(negativo){
				*valor = *valor * -1;
				negativo = 0;
			}
			
			arv_composicao = NULL;
			
			sub_arv = criar_subarvore(valor, 2, NULL, NULL, NULL);
			encaixar_arvore((arv_operador != NULL && arv_operador->esquerda == NULL) ? &arv_operador : &arv,
					arv_composicao, arv_operador, sub_arv);

			continue;
		} else {

			//Se chegou aqui, por construção, só pode ser função
			j = i;
			k = 0;
			expressao_atual[k++] = atual;

			while(((atual_interno = expr[j++]) != '\0') &&
					atual_interno != '('){
				expressao_atual[k++] = atual_interno;
			}
			//Para passar direto do parêntese
			i = ++j;

			//Identificar funcao
			if(procurar(expressao_atual, "sen")){
				sub_arv = criar_subarvore(sin, 0, NULL, NULL, NULL);
			} else if(procurar(expressao_atual, "cos")){
				sub_arv = criar_subarvore(cos, 0, NULL, NULL, NULL);
			} else if(procurar(expressao_atual, "tan")){
				sub_arv = criar_subarvore(tan, 0, NULL, NULL, NULL);
			} else if(procurar(expressao_atual, "arctan")){
				sub_arv = criar_subarvore(atan, 0, NULL, NULL, NULL);
			} else if(procurar(expressao_atual, "arcsen")){
				sub_arv = criar_subarvore(asin, 0, NULL, NULL, NULL);
			} else if(procurar(expressao_atual, "arccos")){
				sub_arv = criar_subarvore(acos, 0, NULL, NULL, NULL);
			} else if(procurar(expressao_atual, "exp")){
				sub_arv = criar_subarvore(exp, 0, NULL, NULL, NULL);
			} else if(procurar(expressao_atual, "ln")){
				sub_arv = criar_subarvore(log, 0, NULL, NULL, NULL);
			} else if(procurar(expressao_atual, "log")){
				sub_arv = criar_subarvore(log10, 0, NULL, NULL, NULL);
			}

			encaixar_arvore(&arv, arv_composicao, arv_operador, sub_arv);
			arv_composicao = sub_arv;
		}

		if(!negativo) poss_neg = 0;
	}

	//if(arv_operador != NULL) arvore_lbr(arv_operador);
	//if(arv_composicao != NULL) arvore_lbr(arv_composicao);
	//if(valor != NULL) free(valor);

	return arv;
}

/*Avalia a expressão descrita em x = @ponto*/
double arvore_avlr(Arvore *arvr, double ponto){
	double direita,
		   esquerda,
		   dentro,
		   saida = -DBL_MAX;

	if(arvr == NULL) return -DBL_MAX;
	else {
		direita = (arvr->direita != NULL) ? arvore_avlr(arvr->direita, ponto) : 0;
		esquerda = (arvr->esquerda != NULL) ? arvore_avlr(arvr->esquerda, ponto) : 0;
		dentro = (arvr->dentro != NULL) ? arvore_avlr(arvr->dentro, ponto) : 0;
		
		switch(arvr->tipo){
			case 0:
				saida = ((func)(arvr->expressao))(dentro);
				break;
			case 1:
				saida = ((operador)(arvr->expressao))(direita, esquerda);
				break;
			case 2:
				saida = *((double *) (arvr->expressao));
				break;
			case 3:
				saida = ponto;
				break;
			default:
				break;
		}
		
	}

	return saida;
}

/*	Liberar árvore de expressões*/
void arvore_lbr(Arvore *arvr){
	if(arvr == NULL) return;
	else {

		if(arvr->tipo == 2) free(arvr->expressao);

		if(arvr->dentro != NULL) arvore_lbr(arvr->dentro);
		if(arvr->direita != NULL) arvore_lbr(arvr->direita);
		if(arvr->esquerda != NULL) arvore_lbr(arvr->esquerda);

		free(arvr);
	}
}
