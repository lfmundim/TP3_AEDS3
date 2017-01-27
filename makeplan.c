#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "makeplan.h"
#include "grid.h"


void calculatePlan(int **grid, int x, int y, int threads_number){
    int i, j;
    plot_t *plot;
    pthread_t threads[threads_number];

    plot = (plot_t*)calloc(threads_number,sizeof(plot_t));

    for(i=0; i<threads_number; i++){
        plot[i].grid_line = makeArray(x);
        for(j=0; j<y; j++)
            plot[i].grid_line[j] = grid[i][j];
        plot[i].threads_number = threads_number;
        plot[i].x = x;
        plot[i].y = y;
        plot[i].answer = makeArray(x);
        plot[i].tid = i;
    }

    for(int cu=0; cu<plot->y; cu++){
        printf("[%d]", plot->grid_line[cu]);
    }
    printf("\n");

    for(i=0; i<threads_number; i++){
        pthread_create(&threads[i], NULL, bestInLine, (void*)&plot[i]);
    }
    for(i=0; i<threads_number; i++){
        pthread_join(threads[i], NULL);
    }

    for(int cu=0; cu<plot->y; cu++){
        printf("[%d]", plot->answer[cu]);
    }
    printf("\n");
}

void bestInLine(void* plot){
    plot_t *plot_p = (plot_t*)plot;
    int *aux, sum;
    aux = makeArray(plot_p->y);

    // for(int cu=0; cu<plot_p->y; cu++){
    //     printf("[%d]", plot_p->grid_line[cu]);
    // }
    // printf("\n");

    for(int i=0; i<plot_p->y; i++){
        if(i==0){
            aux[i]=plot_p->grid_line[i];
        }
        else if(i==1){
            if(plot_p->grid_line[1]>plot_p->grid_line[0])
                aux[i] = plot_p->grid_line[1];
            else
                aux[i] = plot_p->grid_line[0];
        }
        else{
            sum = plot_p->grid_line[i]+aux[i-2];
            if(sum>aux[i-1])
                aux[i] = sum;
            else
                aux[i] = aux[i-1];
        }
    }

    for(int i=0; i<plot_p->y; i++)
            plot_p->answer[i] = aux[i];

    pthread_exit(NULL);
}
