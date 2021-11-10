#include <stdio.h>
#include <stdlib.h>
#include "libGraph.h"

/*goes back until from goal to start. Then prints*/
void printRoute (Vertex visited) { 
    if (visited == NULL) {
        return;
    }
    printRoute(visited->from);
    printf("%s\n", visited->name);
}

/*resets the values modifed to erase the route for next traverse*/
void eraseRoute (Graph railNetwork) {
    int i = 0;
    Vertex temp = railNetwork->stations[i];
    while(temp!=NULL) {
        railNetwork->stations[i]->distance = infinity;
        railNetwork->stations[i]->visited = false;
        railNetwork->stations[i]->from = NULL;
        i++;
        temp = railNetwork->stations[i];
    }
}

/*returns the closest station*/
Vertex closestStation(Graph railNetwork) {
    int i = 0;
    int distance = infinity;
    Vertex V = railNetwork->stations[i];
    Vertex temp = railNetwork->stations[i];
    while (temp!=NULL) {
        if (!temp->visited &&
            temp->distance < distance) {
            distance =temp->distance;
            V = temp;
        }
        i++;
        temp = railNetwork->stations[i];
    }
    return V;
}

/*returns the number of vertices in a graph*/
int nrVertex (Graph railNetwork) {
    int i = 0;
    while(railNetwork->stations[i]) {
        i++;
    }
    return i;
}

int dijkstra (Graph railNetwork, Vertex start, Vertex goal) {
    start->distance = 0; //set initail distance to 0
    Vertex current;

    int nrUnvisited = nrVertex(railNetwork);  //the number of unvisited stations
    while (nrUnvisited) {
        current = closestStation(railNetwork);  //we start at closest station aka least distance
        Edge neighbors = current->neighbour;
        current->visited = true;    //one less unvisited vertex
        if(goal->visited || current->distance == infinity) {    //we stop if goal vertex is visited
            return current->distance;                           //we also stop when the closest one can't be reached
        }
        /*update the distance for the neighbors of the current vertex*/
        while(neighbors != NULL) {
            int weight = current->distance; //weight of edge
            if (neighbors->vertex->distance > neighbors->weight + weight
                && !neighbors->vertex->visited){    //we only update distance when it is less than already found one
                neighbors->vertex->distance = neighbors->weight + weight;
                neighbors->vertex->from = current;  //save where we came here from
            }
            neighbors = neighbors->next;    //move on to next neighbour
        }
        nrUnvisited--;
    }
    return infinity;
}