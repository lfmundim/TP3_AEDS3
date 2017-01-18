#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "grid.h"

int main(int argc, char *argv[]){
    int m, n, **grid, threads;

    //numero de Threads passado por linha de comando
    threads = atoi(argv[1]);

    // Dimensões do Grid
    scanf("%d %d", &m, &n);

    // aloca e preenche Grid
    grid = makeGrid(m,n);

    return 0;
}
