#ifndef LIBGRAPH_H
#define LIBGRAPH_H

#define MAXSIZE 12 /*number of intital stations*/
#define MAXSTRING 11    /*characters in a name*/
/*the previous values are just as a start. Once an overflow happens a reallocation takes place*/
#define string char*    /*ease of reading*/
#define infinity 32767  /*max int value*/
#define NOT_REACHABLE 32767

typedef struct token *Edge;
typedef struct vertex *Vertex;
typedef struct graph *Graph;

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "scanner.h"

typedef struct vertex {
    string name;
    int distance; /*we keep track of distance to a vertex with modifying the weight of an edge*/
    Edge neighbour; /*points to the head of the linked list*/
    Vertex from;    /*our track to the goal*/
    bool visited;
} vertex;

typedef struct token {
    Vertex vertex;
    int weight;
    Edge next;
} token;

typedef struct graph {
    Vertex *stations;
} graph;

void freeGraph(Graph G);
Graph newGraph ();
void makeStation (Graph G, string station);
void removeEdge (Vertex V, Vertex V1);
bool stationExists (Graph G, string name, int *i);
void addEdge (Vertex station, Vertex neighbour, int weight);
void printGraph (Graph G);

#endif