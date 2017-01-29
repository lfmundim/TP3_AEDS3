#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMERO_MAX_PESSOAS 10

int main(void){

	int i, j, x, y;
	FILE *saida;

	printf("Digite o tamanho do seu mapa\n");
	scanf("%d %d", &x, &y);

	saida = fopen("teste", "w"); if(!saida) {perror(NULL); exit(EXIT_FAILURE);}

	srand((unsigned)time(NULL));
	fprintf(saida, "%d %d\n", x, y);

	for(i = 0; i < x; i++){
		for(j = 0; j < y; j++){
			fprintf(saida, "%d ", rand()%NUMERO_MAX_PESSOAS);
		}
		fprintf(saida, "\n");
	}

	return 0;
}