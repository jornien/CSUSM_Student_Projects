/*-----------------------------------------------
 * HW#: HW6
 * Name: Jordan Nienaber
 * Compier: g++
 * File Type: client file
 *-----------------------------------------------
*/

#include <iostream>
#include "dgraph.h"

using namespace std;

int main()
{
  dgraph graph;
  graph.fillTable();
  graph.displayGraph();
  cout << "Degree of C is " << graph.findOutDegree('C') << endl;
  graph.remove();
}
