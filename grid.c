#include "grid.h"

int** makeGrid(int x, int y){
    int i, **grid;

    grid = (int**)calloc((size_t)x, sizeof(int*));
    for(i=0; i<x; i++)
        grid[i] = (int*)calloc((size_t)y, sizeof(int));

    return grid;
}

void fillGrid(int x, int y, int **grid){
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            scanf("%d", &grid[i][j]);
        }
    }
}

int* makeArray(int x){
    int *array;
    array = (int*)calloc((size_t)x, sizeof(int));
    return array;
}

void freeGrid(int x, int **grid){
    int i;

    for(i=0; i<x; i++){
        free(grid[i]);
    }
    free(grid);
}
