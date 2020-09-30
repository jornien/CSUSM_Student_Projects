/*===============================================
 * HW#: HW1P1 stack
 * Name: Jordan Nienaber
 * Compiler: g++
 * File type: stack implementation file
 *===============================================
*/

#include <iostream>
#include "stack.h"

using namespace std;

void stack::push(int toAdd)
{
  if (isFull())
  {
    throw Overflow();
  }
  top++;
  elems[top] = toAdd;
}

void stack::pop(int& toRemove)
{
  if (isEmpty())
  {
    throw Underflow();
  }
  toRemove = elems[top];
  top--;
}

void stack::topElem(int& topElem)
{
  if (isEmpty())
  {
    throw Underflow();
  }
  topElem = elems[top];
}

void stack::displayAll()
{
  if (isEmpty())
  {
    cout << " [ empty ] \n";
  }
  else
  {
    for (int i = top; i >= 0; i--)
    {
      cout << elems[i] << endl;
    }
  }
  cout << "--------------------\n";
}

void stack::clearIt()
{
  if (isEmpty())
  {
    cout << "Stack is already empty\n";
  }
  else
  {
    int temp;
    while (!isEmpty())
    {
      pop(temp);
    }
  }
}
