#ifndef _TILES_H_
#define _TILES_H_

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>

#define MAX_NUM_VARS 20        // Maximum number of variables in a grid-tiling

int hash_coordinates(int *coordinates, int num_indices, int memory_size);

void GetTiles(int tiles[],int num_tilings,float variables[], int num_variables, int memory_size,int hash1=-1, int hash2=-1, int hash3=-1);


#endif

