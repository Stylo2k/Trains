#include "scanner.h"


int main(int argc, char **argv) {
    Graph railNetwork = newGraph();
    makeNetwork(railNetwork);
    printGraph(railNetwork);
    freeGraph(railNetwork);
}