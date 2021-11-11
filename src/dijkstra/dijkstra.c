#include <stdio.h>
#include <stdlib.h>
#include "../libGraph.h"

/**
 * @brief 
 * prints the route taken. By tracing back the steps from the goal
 * @param visited the visited vertex
 */
void printRoute (Vertex visited) { 
    if (visited == NULL) {
        return;
    }
    printRoute(visited->from);
    printf("%s\n", visited->name);
}

/**
 * @brief 
 * resets the values modifed to erase the route for the next graph traverse
 * @param railNetwork the railNetwork to erase the route from
 */
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

/**
 * @brief 
 * checks for the closest station
 * @param railNetwork the railNetwork to use for searchin
 * @return Vertex the closest vertex
 */
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

/**
 * @brief returns the number of vertices in a graph
 * 
 * @param railNetwork the railNetwork to count the number of vertices
 * @return int the number of vertices in a graph
 */
int nrVertex (Graph railNetwork) {
    int i = 0;
    while(railNetwork->stations[i]) {
        i++;
    }
    return i;
}

/**
 * @brief 
 * Dijkstra's Algorithm to find the closest path between two vertices
 * 
 * @param railNetwork the railNetwork to use
 * @param start the start vertex
 * @param goal the end goal
 * @return int the shortest distance between start and goal. Or `Not Reachable`
 */
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
    return NOT_REACHABLE;
}