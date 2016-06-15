/*	Formato de Intruções de ponteiros para funções
	int (*POINTER_NAME)(int a, int b)

• Write a normal function declaration: int callme(int a, int b)
• Wrap the function name with the pointer syntax: int (*callme)(int a, int b)
• Change the name to the pointer name: int (*compare_cb)(int a, int b)
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message){
	if(errno){
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(EXIT_FAILURE);
}

typedef int (*compare_cb) (int a, int b);

int *bubble_sort(/*@null@*/int *numbers, int count, compare_cb cmp){
	int temp = 0;
	int i = 0;
	int j = 0;

	int *target = malloc(count * sizeof(int));
	if(!numbers)
		die("Invalid array.");

	if(!target)
		die("Memory Error.");

	memcpy(target, numbers, count * sizeof(int));

	for(i = 0; i < count; i++){
		for(j = 0; j < count - 1; j++){
			if(cmp(target[j], target[j + 1]) > 0){
				temp = target[j + 1];
				target[j + 1] = target[j];
				target[j] = temp;
			}
		}
	}

	/*@null@*/
	return target;
}

int sorted_order(int a, int b){
	return a - b;
}

int reverse_order(int a, int b){
	return b - a;
}

int strange_order(int a, int b){
	if(a == 0 || b == 0){
		return 0;
	} else {
		return a % b;
	}
}

void test_sorting(int *numbers, int count, compare_cb cmp){
	int i = 0;
	int *sorted = bubble_sort(numbers, count, cmp);

	if(!sorted)
		die("Failed to sort as requested.");

	for(i = 0; i < count; i++){
		printf("%d ", sorted[i]);
	}
	printf("\n");
	free(sorted);
}

void dump(compare_cb cmp){
	int i = 0;
	unsigned char *data = (unsigned char *)cmp;

	for(i = 0; i < 25; i++)  {
		 printf("%02x:", data[i]);
	}

	printf("\n");	
}

int amain(int argc, char *argv[]){
	if(argc < 2)
		die("USAGE: ex18 2 2 3 41 3");

	int count = argc - 1;
	int i = 0;
	char **inputs = argv + 1;
	int *numbers = malloc(count * sizeof(int));
	
	if(!numbers)
		die("Memory Error.");

	for(i = 0; i < count; i++){
		numbers[i] = atoi(inputs[i]);
	}

	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);
	
	free(numbers);
	return 0;
}
