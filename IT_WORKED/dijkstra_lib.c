#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "dij_list.h"

#define MAX_PATH_LEN 1024

char dijkstra_python_buffer[MAX_PATH_LEN];

int size = 33;

Edge adjacency_list[][10] = {
        // K
        { {"X2", 52} },
        // L
        { {"X3", 38} },
        // I
        { {"X4", 69}, {"X6", 73} },
        // J
        { {"X5", 64} },
        // M
        { {"X8", 63} },
        // H
        { {"X7", 95}, {"X8", 22} },
        // N
        { {"X10", 22} },
        // O
        { {"X10", 35} },
        // P
        { {"X12", 56} },
        // C
        { {"X11", 48}, {"X16", 57} },
        // Q
        { {"X13", 52} },
        // B
        { {"X13", 72} },
        // A
        { {"X14", 44} },
        // SI
        { {"X10", 51} },
        // SU
        { {"X15", 100} },
        // X1
        { {"X2", 67}, {"X5", 103} },
        // X2
        { {"K", 52}, {"X1", 67}, {"X3", 113} },
        // X3
        { {"L", 38}, {"X2", 113}, {"X4", 22} },
        // X4
        { {"I", 69}, {"X3", 22}, {"X8", 88} },
        // X5
        { {"J", 64}, {"X6", 45}, {"X1", 103} },
        // X6
        { {"I", 73}, {"X5", 45}, {"X7", 107} },
        // X7
        { {"X6", 107}, {"H", 95}, {"X16", 234} },
        // X8
        { {"M", 63}, {"H", 22}, {"X9", 60}, {"X4", 88} },
        // X9
        { {"X8", 60}, {"X12", 131}, {"X10", 162} },
        // X10
        { {"X9", 162}, {"N", 22}, {"O", 35}, {"SI", 51} },
        // X11
        { {"X12", 35}, {"C", 48}, {"X13", 68} },
        // X12
        { {"P", 56}, {"X11", 35}, {"X9", 131} },
        // X13
        { {"Q", 52}, {"B", 72}, {"X11", 68}, {"X17", 56} },
        // X14
        { {"X18", 32}, {"A", 44} },
        // X15
        { {"X17", 68}, {"SU", 100} },
        // X16
        { {"C", 57}, {"X18", 122}, {"X7", 234} },
        // X17
        { {"X13", 56}, {"X18", 88}, {"X15", 68} },
        // X18
        { {"X14", 32}, {"X16", 122}, {"X17", 88}}
};



char* vertex_datav[] = {
    "K","L","I","J","M","H","N","O",
    "P","C","Q","B","A","SI","SU","X1",
    "X2","X3","X4","X5","X6","X7","X8","X9",
    "X10","X11","X12","X13","X14","X15","X16","X17",
    "X18"
};

int edge_count[] = {
    1, 1, 2, 1, 1, 2, 1, 1,    // K, L, I, J, M, H, N, O
    1, 2, 1, 1, 1, 1, 1, 2,    // P, C, Q, B, A, SI, SU, X1
    3, 3, 3, 3, 3, 3, 4, 3,    // X2, X3, X4, X5, X6, X7, X8, X9
    4, 3, 3, 4, 2, 2, 3, 3,    // X10, X11, X12, X13, X14, X15, X16, X17
    3                          // X18
};


char start[4];
char end[4];



int min_distance(int distances[], bool visited[], int size)
{
    int min = 9999, min_index = -1;
    for (int v = 0; v<size; v++)
    {
        if ( !visited[v] && distances[v] <= min )
        {
            min = distances[v];
            min_index = v;
        }
    }
    return min_index;
}

int findVertex(char **vertex_data, int size, char *node)
{
    int vertex = -1;
    for (int i=0; i < size; i++)
    {
        if (strcmp(vertex_data[i],node) == 0)
        {
            vertex = i;
            break;
        }
    }
    return vertex;
}


char* dijkstra(Edge adjacency_list[33][10],char **vertex_data,int *edge_count, int size, char* start, char* end)
{
    int start_vertex = findVertex(vertex_data,size, start);
    int end_vertex = findVertex(vertex_data,size, end);


    int distances[size];
    bool visited[size];
    char* passedBy[size];

    for (int i=0; i<size;i++)
    {
        distances[i] = 9999;
        visited[i] = false;
        passedBy[i] = NULL;
    }
    distances[start_vertex] = 0;
    for (int i=0; i<size -1; i++)
    {
        int u=min_distance(distances,visited,size);
        visited[u] = true;
        for (int e=0; e< edge_count[u]; e++)
        {
            char* neighbor_char = adjacency_list[u][e].dest;
            int weight = adjacency_list[u][e].weight;
            int neighbor_index = findVertex(vertex_data, size, neighbor_char);

            if (!visited[neighbor_index] &&  distances[neighbor_index] > distances[u] + weight)
            {
                distances[neighbor_index] = distances[u] + weight;
                passedBy[neighbor_index] = vertex_data[u];
            }
        }
    }

    char* rev_nodes[size];
    int count = 0;
    for (int j=0; j<size; j++)
    {
        if (passedBy[end_vertex] == NULL) break;
        rev_nodes[j] = passedBy[end_vertex];
        //printf("%c <- ", passedBy[end_vertex]);
        int new_end_vertex = findVertex(vertex_data,size, passedBy[end_vertex]);
        end_vertex = new_end_vertex;
        count++;
    }


    char* nodes[count+1];
    for (int i = 0; i < count; i++) {
        nodes[i] = rev_nodes[count - i - 1];
    }
    nodes[count] = end;

    dijkstra_python_buffer[0] = '\0';
    for (int i = count - 1; i >= 0; i--) {
        strcat(dijkstra_python_buffer, rev_nodes[i]);
        strcat(dijkstra_python_buffer, ",");
    }
    strcat(dijkstra_python_buffer, end);

    return dijkstra_python_buffer;

}


char* dijkstra_python(char* start, char* end)
{
    return dijkstra(adjacency_list,vertex_datav,edge_count, size, start, end);
}

