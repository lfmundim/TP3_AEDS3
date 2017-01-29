#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "makeplan.h"
#include "grid.h"

void bestInLine(void *plot){
    plot_t *plotaux = (plot_t*)plot;
    int loops = plotaux->x/plotaux->threads_number;
    int endloop = loops*(plotaux->tid+1);
    loops = plotaux->tid*loops;
    int *aux = makeArray(plotaux->y);
    int sum;

    for(int i=loops; i<endloop; i++){
        for(int j=0; j<plotaux->y; j++){
            if(i==0)
                aux[j] = plotaux->matrix[i][j];
            if(i==1){
                if(plotaux->matrix[i][j]>plotaux->matrix[i][j-1])
                    aux[j] = plotaux->matrix[i][j];
                else
                    aux[j] = plotaux->matrix[i][j-1];
            }
            else{
                sum = plotaux->matrix[i][j] + plotaux->matrix[i][j-2];
                if(sum>plotaux->matrix[i][j-1])
                    aux[j] = sum;
                else
                    aux[j] = plotaux->matrix[i][j-1];
            }
        }
    }
    for(int i=0; i<plotaux->y; i++)
        printf("[%d]", aux[i]);
    printf("\n");

}

void calculatePlan(int **grid, int x, int y, int threads_number){
    plot_t plot;
    pthread_t threads[threads_number];

    plot.matrix = makeGrid(x,y);
    for(int i=0; i<x; i++)
        for(int j=0; j<y; j++)
            plot.matrix[i][j] = grid[i][j];
    plot.threads_number = threads_number;
    plot.x = x;
    plot.y = y;
    plot.answer = makeArray(x);

    for(int i=0; i<threads_number; i++){
        plot.tid=i;
        pthread_create(&threads[i], NULL, bestInLine, (void*)&plot);
    }
    for(int i=0; i<threads_number; i++)
        pthread_join(threads[i], NULL);
}
