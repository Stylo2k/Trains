#include "libGraph.h"
#include "dijkstra.h"

/*scans the string for input console*/
string scanStringFromConsole () {
    string name = calloc( (MAXSTRING+1), sizeof(char));
    assert(name!=NULL);
    int i = 0, size = MAXSTRING;
    char c = getchar();
    while (c != '\n' && c != '!') {
        if (i == size) {
            name = realloc(name, (size+10) * sizeof(char));
            size += 10; //update size
        }
        name[i] = c;
        i++;
        c = getchar(); 
    }
    return name;
}

/*find the vertex with the same name and returns it*/
Vertex scanVertex (Graph railNetwork) {
    string name = scanStringFromConsole();
    if (name[0]=='!') {
        free(name);
        return NULL;
    }
    int i = 0;
    stationExists(railNetwork,name,&i);//i holds the index of the vertex
    free(name);
    return railNetwork->stations[i];
}

/*scans where disruption occurs and removes edges*/
void scanDisruptions (Graph railNetwork) {
    int disruptions;
    if(!scanf("%d\n", &disruptions)) {
        printf("disruptions not scanned correctly\n");
    }
    while (disruptions) {
        //scan 2 strings : start, end
        //delete the path from graph
        Vertex start, end;
        start = scanVertex(railNetwork);
        end = scanVertex(railNetwork);
        removeEdge(start,end);  //remove edge on both ends
        removeEdge(end,start);
        disruptions--;
    }
}

/*uses dijkstra's algorithm to traverse graph. After scanning start and end station*/
void traverseNetWork (Graph railNetwork) {
    scanDisruptions(railNetwork);

    int i = 0, j = 0, time = 0;
    Vertex start, goal;
    start = scanVertex (railNetwork);    //vertex where we begin
    if (!start) printf("start not scanned correctly\n");
    while (start) {
        time = i = j = 0;
        goal = scanVertex (railNetwork); //scans goal vertex
        time = dijkstra(railNetwork,start,goal);
        if (time == infinity) { //we have not visited goal station
            printf("UNREACHABLE\n");
        } else {
            printRoute(goal);   //prints route begining at goal tracing back the steps
            printf("%d\n", time);
        }
        eraseRoute(railNetwork);    //resets all modified values
        start = scanVertex(railNetwork);
    }
}

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

int main(int argc, const char **argv) {
    Graph railNetwork = newGraph();
    makeNetwork(railNetwork);
    traverseNetWork(railNetwork);
    freeGraph(railNetwork);
}
