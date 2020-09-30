/*===============================================
 * HW#: HW2P1 binary search
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: client file
 *===============================================
*/

#include <iostream>
#include <vector>
#include "Binsearch.h"

using namespace std;

int main()
{
  vector<int> numbers;

  int toAdd = 0;
  int toFind;

  while (toAdd >= 0)
  {
    cout << "Enter a number to add to the list (enter -1 to finish): ";
    cin >> toAdd;
    numbers.push_back(toAdd);
  }

  numbers = Binsearch :: mergesort(numbers);

  cout << "Enter a number to search for: ";
  cin >> toFind;

  if (Binsearch :: binsearch(numbers, toFind))
  {
    cout << toFind << " is in the list.\n";
  }
  else
  {
    cout << toFind << " is not in the list.\n";
  }


  return 0;
}
