#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "makeplan.h"
#include "grid.h"

void endstep(int *array, int size){
    int sum;

    for(int i=1; i<size; i++){
        if(i==1){
            if(array[i]>array[i-1])
                continue;
            else
                array[i] = array[i-1];
        }
        else{
            sum = array[i] + array[i-2];
            if(sum>array[i-1])
                array[i] = sum;
            else
                array[i] = array[i-1];
        }
    }
    printf("%d\n", array[size-1]);
}


void* bestInLine(void *plot){
    plot_t *plotaux = (plot_t*)plot;
    int sum;

    for(int i=plotaux->tid; i<plotaux->x; i+=plotaux->threads_number){
        for(int j=1; j<plotaux->y; j++){
            if(j==1){
                if(plotaux->matrix[i][j]>plotaux->matrix[i][j-1])
                    continue;
                else
                    plotaux->matrix[i][j] = plotaux->matrix[i][j-1];
            }
            else{
                sum = plotaux->matrix[i][j] + plotaux->matrix[i][j-2];
                if(sum>plotaux->matrix[i][j-1])
                    plotaux->matrix[i][j] = sum;
                else
                    plotaux->matrix[i][j] = plotaux->matrix[i][j-1];
            }
        }

    }
    pthread_exit(NULL);
}

void calculatePlan(int **grid, int x, int y, int threads_number){
    int k, limit, *final, aux;
    plot_t *plot;
    pthread_t *threads;

    if(threads_number>x)
        limit = x;
    else
        limit = threads_number;

    plot = (plot_t*)calloc(limit, sizeof(plot_t));
    threads = (pthread_t*)calloc(limit, sizeof(pthread_t));
    final = makeArray(x);

    for(k=0; k<limit; k++){
        plot[k].matrix = makeGrid(x,y);
        for(int i=0; i<x; i++)
            for(int j=0; j<y; j++)
                plot[k].matrix[i][j] = grid[i][j];
        plot[k].threads_number = threads_number;
        plot[k].x = x;
        plot[k].y = y;
        plot[k].answer = makeArray(x);
    }

    for(int i=0; i<limit; i++){
        plot[i].tid=i;
        pthread_create(&threads[i], NULL, bestInLine, (void*)&plot[i]);
    }
    for(int i=0; i<limit; i++)
        pthread_join(threads[i], NULL);

    for(int i=0; i<x; i++){
        if(i<limit)
            final[i] = plot[i].matrix[i][y-1];
        else{
            aux = i;
            while(aux>=limit)
                aux-=threads_number;
            final[i] = plot[aux].matrix[i][y-1];
        }
    }
    endstep(final, x);
    free(threads);
    for(int a=0; a<limit; a++){
        freeGrid(x, plot[a].matrix);
        free(plot[a].answer);
    }
    free(plot);
    free(final);
}
