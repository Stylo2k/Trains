#ifndef SCANNER_H
#define SCANNER_H

#include "libGraph.h"

string scanLineFromFile (FILE *fp);
Vertex stringToVertex (FILE *fp, Graph network);
void makeSubGraph (FILE *fp, Graph network);
void makeNetwork (Graph network);


#endif