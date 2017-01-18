#include "grid.h"

int** makeGrid(int x, int y){
    int i, j, **grid;

    grid = (int**)calloc((size_t)x, sizeof(int*));
    for(i=0; i<n; i++)
        grid[i] = (int*)calloc((size_t)y, sizeof(int));

    for(i=0; i<x; i++){
        for(j=0; j<y; j++){
            scanf("%d", &grid[i][j]);
        }
    }
    return grid;
}
