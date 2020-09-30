/*-----------------------------------------------
 * HW#: HW7
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: client file
 *-----------------------------------------------
*/

#include <iostream>
#include <vector>
#include "dgraph.h"
#include "llist.h"

using namespace std;

int main()
{
  dgraph graph;
  llist adjacent;
  char current;
  int visitNumber = 1;
  vector<char> vertices;
  graph.fillTable();
  graph.displayGraph();
  graph.visit(visitNumber, 'A');
  visitNumber++;
  adjacent = graph.findAdjacency('A');
  for (int i = 0; i < adjacent.getSize(); i++)
  {
    vertices.push_back(adjacent.getData(i));
  }
  cout << "Current Stack: ";
  for (int i = 0; i < vertices.size(); i++)
  {
    cout << vertices[i] << " ";
  }
  cout << endl;
  while (vertices.size() != 0)
  {
    current = vertices.back();
    vertices.pop_back();
    if (!graph.isMarked(current))
    {
      graph.visit(visitNumber, current);
      visitNumber++;
      adjacent = graph.findAdjacency(current);
      for (int i = 0; i < adjacent.getSize(); i++)
      {
	vertices.push_back(adjacent.getData(i));
      }
      cout << "Current Stack: ";
      for (int i = 0; i < vertices.size(); i++)
      {
	cout << vertices[i] << " ";
      }
      cout << endl;
    }
  }
  graph.displayGraph();
  return 0;
}
