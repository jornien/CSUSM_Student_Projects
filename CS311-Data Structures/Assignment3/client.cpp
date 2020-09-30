/*-----------------------------------------------
 * HW#: HW3P1
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: linked list client file
 *-----------------------------------------------
*/

#include <iostream>
#include "llist.h"

using namespace std;

int main()
{
  llist test;
  
  test.addFront(5);
  test.addFront(6);

  test.addBack(10);
  test.addBack(9);

  test.addBeforeI(2, 7);
  test.addBeforeI(4, 11);
  test.PrintAll();

  test.deleteIth(3);
  test.deleteIth(1);
  test.PrintAll();

  test.deleteFront();
  test.deleteFront();
  test.PrintAll();

  test.deleteBack();
  test.deleteBack();
  test.PrintAll();

  test.ClearAll();

  return 0;
}
