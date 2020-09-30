/*===============================================
 * HW#: HW1P1 stack
 * Name: Jordan Nienaber
 * Complier: g++
 * File Type: stack client file
 *===============================================
*/

#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
  stack postfix;
  string expression;
  
  char symbol;
  int box1;
  int box2;

  cout << "Enter a postfix expression: ";
  cin >> expression;
  
  for (int i = 0; expression[i] != '\0'; i++)
  {
    symbol = expression[i];
    
    try
    {
      if (isdigit(symbol))
      {
        if (!postfix.isFull())
        {
	  postfix.push(symbol - '0');
	}
      }
      else if (symbol == '+' || symbol == '-' || symbol == '*')
      {
        int result;
        postfix.pop(box1);
        postfix.pop(box2);
        if (symbol == '+')
        {
	  result = box2 + box1;
	}
	else if (symbol == '-')
	{
	  result = box2 - box1;
	}
	else
	{
	  result = box2 * box1;
	}
	postfix.push(result);
      }
      else
      {
	throw "invalid item";
      }
    }
    catch (stack::Overflow)
    {
      cerr << "ERROR: Too many numbers in your expression.\n";
      return 0;
    }
    catch (stack::Underflow)
    {
      cerr << "ERROR: Not enough numbers in your expression.\n";
      return 0;
    }
    catch (char const* errorcode)
    {
      cerr << "ERROR: Invalid character.\n";
      return 0;
    }
  }
  
  int result;
  if (!postfix.isEmpty())
  {
    postfix.pop(result);
    if (postfix.isEmpty())
    {
      cout << "Result = " << result << endl;
    }
    else
    {
      cerr << "ERROR: Invalid expression.\n";
    }
  }

  return 0;
}
