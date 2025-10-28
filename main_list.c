#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "dij_list.h"


int main()
{
    int size = 7;

    Edge adjacency_list[7][7] = {
        // A
        { {'C', 3}, {'D', 4}, {'E', 4} },
        // B
        { {'C', 2}, {'F', 2} },
        // C
        { {'A', 3}, {'B', 2}, {'E', 4}, {'F', 5} },
        // D
        { {'A', 4}, {'E', 2} },
        // E
        { {'A', 4}, {'C', 4}, {'D', 2}, {'G', 5} },
        // F
        { {'B', 2}, {'C', 5}, {'G', 5} },
        // G
        { {'E', 5}, {'F', 5} }
    };


    char vertex_datav[7] = {'A','B','C','D','E','F','G'};
    int edge_count[7] = {3,2,4,2,4,3,2};
    char start;
    char end;

    printf("HELLO THERE! LET'S ROLL!\n\n");
    printf("WHERE ARE WE NOW ? ");
    scanf(" %c", &start);
    printf("WHERE ARE WE GOING ? ");
    scanf(" %c", &end);



    dijkstra(adjacency_list,vertex_datav,edge_count, size, start, end);
    return 0;
}

