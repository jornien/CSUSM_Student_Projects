/*===============================================
 * HW#: HW1P2 stack
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: vstack client file
 *===============================================
*/

#include <iostream>
#include <string>
#include "vstack.h"

using namespace std;

int main()
{
  vstack postfix;
  string expression;

  int i = 0;
  char item;

  int box1;
  int box2;
  int result;

  cout << "Enter a postfix expression: ";
  cin >> expression;

  while (expression[i] != '\0')
  {
    try
    {
      item = expression[i];
      if (isdigit(item))
      {
        postfix.push(item - '0');
      }
      else if (item == '-' || item == '+' || item == '*')
      {
        box1 = postfix.pop();
        box2 = postfix.pop();
        if (item == '-')
        {
          postfix.push(box2 - box1);
        }
        else if (item == '+')
        {
          postfix.push(box2 + box1);
        }
        else
        {
	  postfix.push(box2 * box1);
	}
      }
      else
      {
	throw "Invalid Item";
      }
    }
    catch (vstack :: Underflow)
    {
      cerr << "ERROR: Not enough numbers in the expression\n";
      return 0;
    }
    catch(const char* errorcode)
    {
      cerr << "ERROR: Invalid character\n";
      return 0;
    }
    i++;
  }

  if (!postfix.isEmpty())
  {
    result = postfix.pop();
    if (postfix.isEmpty())
    {
      cout << "result = " << result << endl;
    }
    else
    {
      cerr << "ERROR: Incomplete expression.\n";
    }
  }

  return 0;
}
