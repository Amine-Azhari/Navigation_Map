typedef struct {
    char dest;
    int weight;
}Edge;

int min_distance(int distances[], bool visited[], int size);
void dijkstra(Edge adjacency_list[7][7],char *vertex_data,int *edge_count, int size, char start, char end);
int findVertex(char *vertex_data, int size, char node);
