#include "../libGraph.h"

/**
 * @brief 
 * makes a new graph.
 * The graph is made out of multiple vertices. Called Stations
 * 
 * @return returns a new graph instance
 */
Graph newGraph () {
    Graph G = malloc(sizeof (struct graph));
    assert(G!=NULL);
    G->stations = calloc( (MAXSIZE+1), sizeof (Vertex)); /* +1 to indicate the end (NULL)*/
    assert(G->stations!=NULL);
    return G;
}

/**
 * @brief 
 * Makes a vertex, aka a station.
 * @param G the graph to which the stations should be added
 * @param station the name of the station
 */
void makeStation (Graph G, string station) {
    static int i = 0; static int size = MAXSIZE;    //static to keep their values
    string copy = station;  //we exchange the pointers instead of using strcpy
    station = NULL; //make initial pointer point to NULL to not change copy
    Vertex temp = calloc(1,sizeof(struct vertex));  //calloc takes care of initialization other entities to NULL
    assert(temp!=NULL);
    temp->name = copy;  //assign name of station
    temp->distance = infinity;
    /*for if stations > 12 */
    if (i == size) {
        size = size * 2;
        G->stations = realloc(G->stations, (size+1) * sizeof (Vertex));
    }
    G->stations[i] = temp; //add station to railNetwork aka graph
    i++;
}

/**
 * @brief 
 * checks whether a station exists and returns `i` holds the index of the pointer pointing to that station
 * @param G the graph to search for the station in
 * @param name the name of the station
 * @param i pointer to the index where the station is located in the graph
 * @return true if the station exists
 * @return false if the station does not exist
 */
bool stationExists (Graph G, string name, int *i) {
    while (G->stations[(*i)] != NULL) {
        if (!strcmp(G->stations[(*i)]->name, name)) { /*returns 0 if name == name*/
            return true;
        }
        (*i)++;
    }
    return false;
}

/**
 * @brief makes a node between two vertices
 * 
 * @param neighbour the neighbour to connect to
 * @param weight the weight of the edge
 * @return Edge the edge with the weight now connected to the neighbour
 */
Edge makeEdge (Vertex neighbour, int weight) {
    Edge temp = malloc(sizeof(struct token));
    assert(temp!=NULL);
    temp->vertex = neighbour;
    temp->weight = weight;
    temp->next = NULL;
    return temp;
}

/**
 * @brief adds an edge between two vertices.
 * Notice! the edge is put in ascending order.
 * @param station the station of origin
 * @param neighbour the neighbour to connect to
 * @param weight the weight of the edge
 */
void addEdge (Vertex station, Vertex neighbour, int weight) {
    Edge E = makeEdge(neighbour, weight);
    /*start of linked list*/
    if ((station)->neighbour == NULL || weight <= (station)->neighbour->weight) { 
        E->next = (station)->neighbour;
        (station)->neighbour = E;
    } else {    //not first node
        Edge temp = (station)->neighbour;
        /*we keep looping until a value is higher*/
        while(temp->next != NULL && temp->next->weight < weight) {
            temp = temp->next;
        }
        E->next = temp->next;
        temp->next = E;
    }
}

/**
 * @brief removes an edge between two vertices. For example:
 * when a distribution occurs
 * @param V the vertex of origin
 * @param V1 the vertex the origin is connected to
 */
void removeEdge (Vertex V, Vertex V1) {
    Edge E = V->neighbour;
    if (E->vertex == V1) {  //first edge
        V->neighbour = V->neighbour->next;
        free(E);
        return;
    }
    while(E->next && E->next->vertex != V1) {
        E = E->next;
    }
    Edge E1 = E->next;
    E->next = E->next->next;
    free(E1);
}

/**
 * @brief prints all the graph into terminal
 * 
 * @param G the graph to print
 */
void printGraph (Graph G) {
    for (int i=0; G->stations[i] != NULL; i++) {
        printf("%s", G->stations[i]->name);
        Edge E = G->stations[i]->neighbour;
        while (E != NULL) {
            printf("\n to ->  %s", E->vertex->name);
            printf(" : %d.", E->weight);
            E = E->next;
        }
        printf("\n\n");
    }
}

/**
 * @brief frees all edges
 * 
 * @param E edge to free
 */
void freeEdges (Edge E) {
    if (E == NULL) {
        return;
    }
    freeEdges(E->next);
    free(E);
}

/**
 * @brief frees all the graph by freeing all vertices and edges
 * 
 * @param G the graph to free
 */
void freeGraph(Graph G) {
    for (int i=0;G->stations[i] != NULL;i++) {
        freeEdges(G->stations[i]->neighbour);
        free(G->stations[i]->name);
        free(G->stations[i]);
    }
    free(G->stations);
    free(G);
}