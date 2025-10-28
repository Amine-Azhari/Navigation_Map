#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "dij.h"


int main()
{
    int size = 7;
    int adjacency_matrix[7][7] = {
    //   A   B   C   D   E   F   G
    {  0, 99,  3,  4,  4, 99, 99 }, // A
    { 99,  0,  2, 99, 99,  2, 99 }, // B
    {  3,  2,  0, 99,  4,  5, 99 }, // C
    {  4, 99, 99,  0,  2, 99, 99 }, // D
    {  4, 99,  4,  2,  0, 99,  5 }, // E
    { 99,  2,  5, 99, 99,  0,  5 }, // F
    { 99, 99, 99, 99,  5,  5,  0 }  // G
    };

    char vertex_datav[7] = {'A','B','C','D','E','F','G'};

    dijkstra(adjacency_matrix,vertex_datav, size, 'A', 'F');
    return 0;
}
