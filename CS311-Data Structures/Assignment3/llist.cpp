/*-----------------------------------------------
 * HW# HW3P1
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: linked list implementation file
 *-----------------------------------------------
*/

#include <iostream>
#include "llist.h"

using namespace std;

void llist :: addFront(int data)
{
  size++;
  //empty list
  if (head == NULL && tail == NULL)
  {
    head = new node(data);
    tail = head;
    return;
  }
  if (head -> next == NULL)
  {
    tail = new node (head -> data);
    head -> data = data;
    head -> next = tail;
    return;
  }
  node* temp = new node(data);
  temp -> next = head;
  head = temp;
}

void llist :: addBack(int data)
{
  size++;
  //empty list
  if (head == NULL && tail == NULL)
  {
    tail = new node(data);
    head = tail;
    return;
  }
  if (head -> next == NULL)
  {
    tail = new node(data);
    head -> next = tail;
    return;
  }
  tail -> next = new node(data);
  tail = tail -> next;
}

//assume i is not by array counting (ie 1 is 1st elem, not 2nd)
void llist :: addBeforeI(int i, int data)
{
  i--;
  if (i >= size)
  {
    cout << "llist has no " << i << "th element\n";
    return;
  }
  if (i == 0)
  {
    addFront(data);
    return;
  }
  node* temp = new node(data);
  node* counter = head;
  for (int j = 0; j < i - 1; j++)
  {
    counter = counter -> next;
  }
  temp -> next = counter -> next;
  counter -> next = temp;
}

void llist :: deleteFront()
{
  if (head == NULL)
  {
    cout << "empty llist\n";
    return;
  }
  if (size == 1)
  {
    delete head;
    delete tail;
    head = tail = NULL;
    size--;
    return;
  }
  node* temp = head;
  head = head -> next;
  delete temp;
  size--;
}

void llist :: deleteBack()
{
  if (tail == NULL)
  {
    cout << " empty llist\n";
    return;
  }
  if (size == 1)
  {
    delete tail;
    delete head;
    tail = head = NULL;
    size--;
    return;
  }
  node* newTail = head;
  while (newTail -> next != tail)
  {
    newTail = newTail -> next;
  }
  tail = newTail;
  delete tail -> next;
  tail -> next = NULL;
}

//assume i is not by array counting (ie 1 is 1st elem, not 2nd)
void llist :: deleteIth(int i)
{
  i--;
  if (i >= size)
  {
    cout << " llist has no " << i << "th element\n";
    return;
  }
  if (i == 0)
  {
    deleteFront();
    return;
  }
  node* counter = head;
  for (int j = 0; j < i - 1; j++)
  {
    counter = counter -> next;
  }
  node* temp = counter -> next;
  counter -> next = counter -> next -> next;
  delete temp;
}

void llist :: PrintAll()
{
  node* temp = head;
  for (int i = 0; temp != NULL; i++)
  {
    cout <<  temp -> data << " ";
    temp = temp -> next;
  }
  cout << endl;
}

void llist :: ClearAll()
{
  cout << "calling llist destructor\n";
  while (size > 0)
  {
    deleteFront();
  }
}
