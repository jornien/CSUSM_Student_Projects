/*-----------------------------------------------
 * HW#: HW3P1
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: linked list header file
 *-----------------------------------------------
*/

#include <iostream>
using namespace std;

struct node
{
  int data;
  node* next;
  node() {next = NULL;};
  node (int d) {data = d; next = NULL;};
};

class llist
{
  protected:
    int size;
    node* head;
    node* tail;
  public:
    llist() {head = NULL; tail = NULL; size = 0;};
    llist(int data) {head = new node(data); tail = head; size = 0;};
    void addFront(int data);
    void addBack(int data);
    void addBeforeI(int i, int data);
    void deleteFront();
    void deleteBack();
    void deleteIth(int i);
    void PrintAll();
    void ClearAll();
};
