#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>

int** makeGrid(int x, int y);

void fillGrid(int x, int y, int **grid);

void freeGrid(int x, int **grid);

int* makeArray(int x);

#endif
