
/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

NODE;

typedef struct g
{
    int num_nodes;
    int *visited;
    struct Node **adjacency_lists;
}
GPH;

typedef struct s
{
    int t;
    int capacity;
    int *arr;
} STK;

NODE *create_node(int v)
{
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *graph,int src,int dest)
{
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;
    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

GPH *create_g(int v)
{
    int i;
    GPH *graph = malloc(sizeof(GPH));
    graph->num_nodes = v;
    graph->adjacency_lists = malloc(sizeof(NODE *) *v);
    graph->visited = malloc(sizeof(int) *v);

    for (int i = 0; i < v; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STK *create_s(int scap)
{
    STK *stack = malloc(sizeof(STK));
    stack->arr = malloc(scap*sizeof(int));
    stack->t = -1;
    stack->capacity = scap;

    return stack;
}

void push(int value,STK *s)
{
    s->t = s->t+1;
    s->arr[s->t] = value;
}

void DFS(GPH *graph,STK *stack,int current_node)
{
    NODE *adj_list = graph->adjacency_lists[current_node];
    NODE *aux = adj_list;

    graph->visited[current_node] = 1;

    //printf("%d ",v_nr);

    push(current_node,stack);

    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (graph->visited[con_ver] == 0)
            DFS(graph, stack, con_ver);
        aux=aux->next;
    }
}

void insert_edges(GPH *graph,int num_edges,int num_nodes)
{
    int src,dest,i;
    printf("Adauga %d munchii (de la 1 la %d)\n",num_edges,num_nodes);
    for (i = 0; i < num_edges; i++)
    {
        scanf("%d%d",&src,&dest);

        src--;
        dest--;

        add_edge(graph,src,dest);
    }
}

void wipe(GPH *graph, int num_nodes)
{
    for (int i = 0; i < num_nodes; i++)
    {
        graph->visited[i] = 0;
    }
}

int canbe(GPH *graph, int a, int b, int num_nodes, STK * dfs_stack)// 0 sau 1 daca poate fi sau nu ajuns
{
    DFS(graph, dfs_stack, a);
    int found = 0;

    for (int i = 0; i <= dfs_stack->t; i++) {
        if (dfs_stack->arr[i] == b) {
            found = 1;
            break;
        }
    }

    wipe(graph, num_nodes);
    return found;
}


int main()
{

    int num_nodes;
    int num_edges;
    int start_node;
    int end_node;
    int path_exists;

    printf("Cate noduri (restaurante) are graful?");
    scanf("%d", &num_nodes);

    printf("Cate muchii (restaurante) are graful?");
    scanf("%d", &num_edges);

    GPH *graph = create_g(num_nodes);
    STK *dfs_stack = create_s(2 * num_nodes);

    insert_edges(graph, num_edges, num_nodes);

    printf("Introdu doua noduri intre care sa verifici drumul: ");
    scanf("%d", &start_node);
    scanf("%d", &end_node);

    start_node--;
    end_node--;

    path_exists = canbe(graph, start_node, end_node, num_nodes, dfs_stack);

    if (path_exists == 1)
        printf("Exista drum intre %d si %d\n", start_node + 1, end_node + 1);
    else
        printf("Nu exista drum intre %d si %d\n", start_node + 1, end_node + 1);

    free(dfs_stack->arr);
    free(dfs_stack);
    free(graph->visited);
    free(graph->adjacency_lists);
    free(graph);

    return 0;
}

