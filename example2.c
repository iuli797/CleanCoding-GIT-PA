/*parcurgerge  graf cu DFS/BFS*/

//Imi cer scuze in avans

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GPH;

/// utils
NODE *create_node(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH *create_graph(int vertices)
{
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));



    graph->visited = malloc(sizeof(int) * vertices);
    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] =       NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GPH *graph, int start_node, int end_node)
{
    NODE *new_node = create_node(end_node);

    new_node->next = graph->adjacency_lists[start_node];
    graph->adjacency_lists[start_node] = new_node;

    new_node = create_node(start_node);

    new_node->next = graph->adjacency_lists[end_node];
    graph->adjacency_lists[end_node] = new_node;
}

void insedg(int num_nodes, int num_edges, GPH *graph)
{
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", num_edges, num_nodes);
    for (i = 0; i < num_edges; i++)
    {
        scanf("%d%d", &src, &dest);
        src--;
        dest--;

        add_edge(graph, src, dest);
    }
}
/// bfs utils
int is_empty(NODE *queue)
{
    return
        queue == NULL;
}

void enqueue(NODE ***queue, int data)
{
    NODE *new_node = create_node(data);

    if (is_empty(*queue)) *queue = new_node;
    else
    {
        NODE *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue)
{
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    return data;
}

void print_graph(GPH *graph)
{
    int i;
    for (i = 0; i < graph->vertices; i++)
    {
        printf("Nod %d: ", i + 1);
        NODE *temp = graph->adjacency_lists[i];

        while (temp)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void print_queue(NODE *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}


void wipe_visited_list(GPH *graph, int num_nodes)
{
    for (int i = 0;
            i < num_nodes;
            i++)
    {
        graph->visited[i] = 0;
    }
}
// parcurgeri
void DFS(GPH *graph, int current_node)
{
    NODE *adj_list = graph->adjacency_lists[current_node];
    NODE *temp = adj_list;

    graph->visited[current_node] = 1;
    printf("%d ", current_node + 1);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GPH *graph, int start)
{
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current + 1);

        NODE *temp = graph->adjacency_lists[current];

        while (temp)
        {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main()
{

    int num_nodes;
    int num_edges;
    int starting_vertex;


    printf("Cate noduri are graful?");
    scanf("%d", &num_nodes);

    printf("Cate muchii are graful?");
    scanf("%d", &num_edges);

    GPH *graph = create_graph(num_nodes);
    insedg(num_nodes, num_edges, graph);

    printf("De unde plecam in DFS?");
    scanf("%d", &starting_vertex); // =)))
    starting_vertex --;

    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);

    wipe_visited_list(graph, num_nodes);
    printf("\n");

    printf("De unde plecam in BFS?");
    scanf("%d", &starting_vertex);
    starting_vertex --;

    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);

    return 0;
}
