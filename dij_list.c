#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    char dest;
    int weight;
}Edge;

int min_distance(int distances[], bool visited[], int size)
{
    int min = 99, min_index = -1;
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

int findVertex(char *vertex_data, int size, char node)
{
    int vertex = -1;
    for (int i=0; i < size; i++)
    {
        if (vertex_data[i] == node)
        {
            vertex = i;
            break;
        }
    }
    return vertex;
}


void dijkstra(Edge adjacency_list[7][7],char *vertex_data,int *edge_count, int size, char start, char end)
{
    int start_vertex = findVertex(vertex_data,size, start);
    int end_vertex = findVertex(vertex_data,size, end);

    int distances[size];
    bool visited[size];
    char passedBy[size];

    for (int i=0; i<size;i++)
    {
        distances[i] = 99;
        visited[i] = false;
        passedBy[i] = '_';
    }
    distances[start_vertex] = 0;
    for (int i=0; i<size -1; i++)
    {
        int u=min_distance(distances,visited,size);
        visited[u] = true;
        for (int e=0; e< edge_count[u]; e++)
        {
            char neighbor_char = adjacency_list[u][e].dest;
            int weight = adjacency_list[u][e].weight;
            int neighbor_index = findVertex(vertex_data, size, neighbor_char);

            if (!visited[neighbor_index] &&  distances[neighbor_index] > distances[u] + weight)
            {
                distances[neighbor_index] = distances[u] + weight;
                passedBy[neighbor_index] = vertex_data[u];
            }
        }
    }
    printf("Dijkstra's Algorithm starting from vertex %c to %c: \n\n", start, end);

    printf("Shortest distance from %c to %c: %d ", start, end, distances[end_vertex]);
    printf("passed by : ");

    char rev_nodes[size];
    int count = 0;
    for (int j=0; j<size; j++)
    {
        if (passedBy[end_vertex] == '_') break;
        rev_nodes[j] = passedBy[end_vertex];
        //printf("%c <- ", passedBy[end_vertex]);
        int new_end_vertex = findVertex(vertex_data,size, passedBy[end_vertex]);
        end_vertex = new_end_vertex;
        count++;
    }


    char nodes[count];
    for (int i=0; i<count; i++)
    {
        nodes[count - i - 1] = rev_nodes[i];
    }


    for (int i=0; i<count; i++)
    {
        printf(" %c ", nodes[i]);
    }

    printf("\n\n");
}

