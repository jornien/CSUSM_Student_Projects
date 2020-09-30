/*===============================================
 * HW#: HW1P1 queue
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: queue header file
 *===============================================
*/

#include <iostream>
#include <string>

using namespace std;

const int MAX = 44;

class queue
{
  private:
    string elems[MAX];

    int count;
    int front;
    int rear;

  public:
    queue() {count = front = 0; rear = -1;};
    ~queue() {};

    class Overflow{};
    class Underflow{};

    void add(string toAdd);
    void remove(string& toRemove);
    void frontElem(string& frontElem);
    
    bool isEmpty() {return count == 0;};
    bool isFull() {return count == MAX;};

    int getSize() {return count;};
    void displayAll();
    void goToBack();
};
