#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "grid.h"
#include "makeplan.h"

int main(int argc, char *argv[]){
    int m, n, **grid, threads_number;

    //numero de Threads passado por linha de comando
    // threads_number = atoi(argv[1]);
    threads_number = 1;

    // Dimensões do Grid
    scanf("%d %d", &m, &n);

    // aloca e preenche Grid
    grid = makeGrid(m,n);
    fillGrid(m,n,grid);

    calculatePlan(grid, m, n, threads_number);

    return 0;
}
