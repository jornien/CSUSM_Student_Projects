/*-----------------------------------------------
 * HW#: HW6
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: dgraph implementation file
 *-----------------------------------------------
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>
#include "llist.h"
#include "dgraph.h"

void dgraph :: displayGraph()
{
  for (int i = 0; i < GTable.size(); i++)
  {
    cout << GTable[i].name << " " << GTable[i].outDegree << " ";
    GTable[i].adjacent.PrintAll();
  }
}

void dgraph :: fillTable()
{
  char vertex;
  int degree;
  string line;
  istringstream iss;
  ifstream  input ("table.txt");
  if (input.is_open())
  {
    while(getline(input, line))
    {
      GVertex temp;
      iss.str(line);
      iss >> vertex >> degree;
      temp.name = vertex;
      temp.outDegree = degree;
      for (int i = 0; i < degree; i++)
      {
        iss >> vertex;
        temp.adjacent.addBack(vertex);
      }
      GTable.push_back(temp);
      iss.clear();
    }
    input.close();
  }
  else
  {
    cout << "Error opening file\n";
  }
}

int dgraph :: findOutDegree(char vertex)
{
  for (int i = 0; i < GTable.size(); i++)
  {
    if (GTable[i].name == vertex)
    {
      return GTable[i].outDegree;
    }
  }
  cout << "Vertex not in graph\n";
  return -1;
}

llist dgraph :: findAdjacency(char vertex)
{
  llist toReturn;
  for (int i = 0; i < GTable.size(); i++)
  {
    if (GTable[i].name == vertex)
    {
      toReturn = GTable[i].adjacent;
      return toReturn;
    }
  }
  cout << "Vertex not in graph\n";
  return toReturn;
}
