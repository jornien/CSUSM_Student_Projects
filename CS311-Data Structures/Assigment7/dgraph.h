/*-----------------------------------------------
 * HW#: HW7
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: dgraph header file
 *-----------------------------------------------
*/

#include<iostream>
#include "llist.h"
#include <vector>

using namespace std;

#ifndef _DGRAPH_H_
#define _DGRAPH_H_

struct GVertex
{
  char name;
  int visitNumber;
  int outDegree;
  llist adjacent;
};

class dgraph
{
  private:
    vector<GVertex> GTable;
  public:
    dgraph(){};
    void displayGraph();
    void fillTable();
    int findOutDegree(char vertex);
    llist findAdjacency(char vertex);
    void remove() {};
    void visit(int visitNumber, char vertex);
    bool isMarked(char vertex);
};

#endif
