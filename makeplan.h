#ifndef MAKEPLAN_H
#define MAKEPLAN_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *grid_line;
    int **matrix;
    int x,y;
    int threads_number;
    int *answer;
    int tid, begin, end;
}plot_t;

void bestInLine(void *plot);

void calculatePlan(int **grid, int x, int y, int threads_number);


#endif
