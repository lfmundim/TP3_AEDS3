#ifndef MAKEPLAN_H
#define MAKEPLAN_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int **matrix;
    int x,y;
    int threads_number;
    int *answer;
    int tid;
}plot_t;

void bestInLine(void *plot);

void calculatePlan(int **grid, int x, int y, int threads_number);


#endif
