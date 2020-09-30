/*-----------------------------------------------
 * HW#: HW4
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: client file
 *-----------------------------------------------
*/

#include <iostream>
#include "binstree.h"

using namespace std;

int main()
{
  binstree test;
  for (int i = 0; i <= 10; i++)
  {
    test.insertNode(i);
  }
  cout << "Unbalanced\n";
  test.PreOrder();

  test.balanceTree();
  cout << "Balanced\n";
  cout << "PreOrder Traversal\n";
  test.PreOrder();
  cout << "InOrder Traversal\n";
  test.InOrder();
  cout << "PostOrder Traversal\n";
  test.PostOrder();

  for (int i = 0; i <= 2; i++)
  {
    test.deleteNode(i * 3);
  }

  cout << "tree after 0, 3, and 6 are removed\n";
  test.PreOrder();

  test.remove();
  return 0;
}
