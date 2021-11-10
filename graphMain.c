#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "libGraph.h"

/*scans a line from the file character by character and returns the string*/
string scanLineFromFile (FILE *fp) {
    string name = calloc( (MAXSTRING+1), sizeof(char));
    assert(name!=NULL);
    char c = fgetc(fp);
    int i = 0 ;
    while (c != '\n') {
        if (i == MAXSTRING) {   /*if a station name is longer than 11(MAXSTRING) chars*/
            name = realloc(name,MAXSTRING+10 * sizeof(char));
        }
        name[i] = c;
        c = fgetc(fp);
        i++;
    }
    return name;
}

/*looks for the vertex in the graph with the same name. If that vertex does not exists
 *then make a new one.*/
Vertex stringToVertex (FILE *fp, Graph network) {
    string name = scanLineFromFile(fp);
    int i = 0;
    if (!stationExists(network, name, &i)) { /*check if station exists*/
        makeStation(network, name);
    } else {
        free(name);
    }
    return network->stations[i];
}

/*makes a subgraph of 2 vertices and one edge*/
void makeSubGraph (FILE *fp, Graph network) {
    /*pos holds the index of the vetices in the array of pointers*/
    Vertex start= stringToVertex(fp,network);
    Vertex end = stringToVertex(fp,network);
    /*next line is the weight of the edge with a new line char*/
    int weight = 0;
    fscanf(fp, "%d\n", &weight);
    /*here we have 2 vertices with an edge weight to connect*/
    addEdge(start, end, weight);   //make edge on both ends
    addEdge(end, start, weight);
}

/*construcs a network*/
void makeNetwork (Graph network) {
    FILE *fp;
    /*File pointer to read the file with the edges and vertices to make*/
    fp = fopen("railNetwork.txt", "r");
    /*while loop scans name and makes the graph*/
    fpos_t pos; fgetpos(fp, &pos);
    while (!feof(fp)) { /*end of file of fp*/
        fsetpos(fp, &pos); //assign a position for file pointer (fgetc modifies the pointer position)
        /*makes a sub graph from file (vertex, vertex, edge)*/
        makeSubGraph(fp, network);
        
        fgetpos(fp, &pos); //backs up the file pointer position
        fgetc(fp);
    }
    fclose(fp);
}

int main(int argc, char **argv) {
    Graph railNetwork = newGraph();
    makeNetwork(railNetwork);
    printGraph(railNetwork);
    freeGraph(railNetwork);
}