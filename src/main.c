#include "libGraph.h"
#include "dijkstra.h"

/**
 * @brief 
 * scans the string for input console
 * @return string the string scanned
 */
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

/**
 * @brief finds the vertex with the same name and returns it
 * 
 * @param railNetwork the railNetwork to look for the vertex in
 * @return Vertex the Vertex found or NULL in case not found
 */
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

/**
 * @brief scans where disruption occurs and removes edges
 * 
 * @param railNetwork the railNetwork to change
 */
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

/**
 * @brief uses dijkstra's algorithm to traverse graph.
 * After scanning disruptions, start and end station
 * 
 * @param railNetwork the railNetwork to traverse
 */
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
        if (time == NOT_REACHABLE) { //we have not visited goal station
            printf("UNREACHABLE\n");
        } else {
            printRoute(goal);   //prints route begining at goal tracing back the steps
            printf("%d\n", time);
        }
        eraseRoute(railNetwork);    //resets all modified values
        start = scanVertex(railNetwork);
    }
}

int main(int argc, const char **argv) {
    Graph railNetwork = newGraph();
    makeNetwork(railNetwork);
    traverseNetWork(railNetwork);
    freeGraph(railNetwork);
}
