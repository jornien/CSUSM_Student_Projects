/*===============================================
 * HW#: HW2P1 binary search
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: binary search header file
 *===============================================
*/ 

#include <iostream>
#include <vector>

using namespace std;

class Binsearch
{
  private:
    static vector<int> combine(vector<int> left, vector<int> right);
  public:
    static bool binsearch(vector<int> numbers, int toFind);
    static vector<int> mergesort(vector<int> numbers);
};
