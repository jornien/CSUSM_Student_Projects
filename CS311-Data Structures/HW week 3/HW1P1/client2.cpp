/*===============================================
 * HW#: HW1P1 queue
 * Name: Jordan Nienaber
 * Complier: g++
 * File Type: queue client file
 *===============================================
*/

#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

int main()
{
  queue phrases;
  phrases.add("A");
  phrases.add("B");
  phrases.add("C");

  while(true)
  {
    try
    {
      string tried;
      
      if (!phrases.isEmpty())
      {
        phrases.remove(tried);
      }

      cout << tried << endl;
      if (!phrases.isFull())
      {
        phrases.add(tried + "A");
        phrases.add(tried + "B");
        phrases.add(tried + "C");
      }
    }
    catch(queue::Overflow)
    {
      cerr << "ERROR: Queue full.\n";
      return 0;
    }
    catch(queue::Underflow)
    {
      cerr << "ERROR: Not enough phrases.\n";
      return 0;
    }
  }
}
