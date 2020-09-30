/*===============================================
 * HW#: HW1P1 queue
 * Name: Jordan Nienaber
 * Complier: g++
 * File Type: queue implementation file
 *===============================================
*/

#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

void queue::add(string toAdd)
{
  if (isFull())
  {
    throw Overflow();
  }
  rear = (rear+1) % MAX;
  elems[rear] = toAdd;
  count++;
}

void queue:: remove(string& toRemove)
{
  if (isEmpty())
  {
    throw Underflow();
  }
  toRemove = elems[front];
  front = (front + 1) % MAX;
  count--;
}

void queue::frontElem(string& frontElem)
{
  if (isEmpty())
  {
    throw Underflow();
  }
  frontElem = elems[front];
}

void queue::displayAll()
{
  if (isEmpty())
  {
    cout << " [ empty ] \n";
  }
  else
  {
    int temp = front;
    for (int i = 0; i < count; i++)
    {
      cout << " [ " << elems[temp] << " ] " <<  endl;
      temp = (temp + 1) % MAX;
    }
  }
}

void queue::goToBack()
{
  string temp;
  remove(temp);
  add(temp);
}
