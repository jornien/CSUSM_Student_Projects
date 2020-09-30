/*===============================================
 * HW#: HW1P1 stack
 * Name: Jordan Nienaber
 * Compiler: g++
 * File type: stack header file
 *===============================================
*/

#include <iostream>

using namespace std;

const int MAX = 10;

class stack
{
  private:
    int elems[MAX];
    int top;
  public:
    class Overflow{};
    class Underflow{};

    stack() {top = -1;};
    ~stack() {};

    void push(int toAdd);
    void pop(int& toRemove);
    void topElem(int& topElem);

    bool isEmpty() {return top == -1;};
    bool isFull() {return top == MAX - 1;};

    void displayAll();
    void clearIt();
};
