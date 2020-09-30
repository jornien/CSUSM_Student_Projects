/*===============================================
 * HW#: HW1P2 stack
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: header file
 *===============================================
*/

#include <iostream>
#include <vector>
using namespace std;

class vstack
{
  private:
    vector<int> numbers;
  
  public:
    class Overflow{};
    class Underflow{};

    vstack() {};
    ~vstack() {};

    void push(int toAdd);
    int pop();
    int topElem();
 
    bool isEmpty() {return numbers.size() == 0;};
    bool isFull() {return false;};
    
    void displayAll();
    void clearIt();
};
