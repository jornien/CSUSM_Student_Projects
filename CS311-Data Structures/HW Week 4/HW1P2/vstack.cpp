/*===============================================
 * HW#: HW1P2 stack
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: vstack implementation file
 *===============================================
*/

#include <iostream>
#include <vector>
#include "vstack.h"

using namespace std;

void vstack :: push(int toAdd)
{
  numbers.push_back(toAdd);
}

int vstack :: pop()
{
  if (isEmpty())
  {
    throw Underflow();
  }
  int toReturn = numbers.back();
  numbers.pop_back();
  return toReturn;
}

int vstack :: topElem()
{
  if (isEmpty())
  {
    throw Underflow();
  }
  return numbers.back();
}

void vstack :: displayAll()
{
  if (isEmpty())
  {
    cout << " [ empty ] \n";
  }
  else
  {
    for (int i = 0; i < numbers.size(); i++)
    {
      cout << numbers[i] << endl;
    }
  }
}

void vstack :: clearIt()
{
  while (numbers.size() > 0)
  {
    pop();
  }
}
