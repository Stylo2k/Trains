#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "libGraph.h"

Vertex closestStation(Graph railNetwork);
void eraseRoute (Graph G);
void printRoute (Vertex V);
int dijkstra (Graph railNetwork, Vertex start, Vertex goal);

#endif