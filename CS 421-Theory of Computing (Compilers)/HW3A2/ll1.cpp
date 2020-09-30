
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

//---------------------------------------
// CS421 File ll1.cpp for HW3A LL1 Table-Driven Parser
// Your name: Jordan Nienaber
//---------------------------------------

// Complete this to fit the HW3A specification - look for **
// Must have the same types of tracing couts as my demo program.

// Feel free to use a stack class or use a vector
// to implement your stack.  The stack will contain characters.

vector<char> stack;
vector<char> M[3][2];  // the table of rules 
                       // 3 rows for S, A, B
                       // 2 rows for 0, 1
       // Each slot contains a rule's right side
       // which is a vector of characters

//  ------- conversion functions ------------------------


// to convert non-terms S, A, B to table rows 0, 1, 2
int toRow(char C)
{
  if (C == 'S')
    return 0;
  else if (C == 'A')
    return 1;
  else if (C == 'B')
    return 2;

  return -1;
}

// to convert '0' and '1' to table columns 0 and 1 
int toCol(char c)
{
  if (c == '0')
    return 0;
  else if (c == '1')
    return 1;

  return -1;
}

// to convert row 0, 1, 2 to non-terms S, A and B
char toNonterm(int r)
{
  if (r == 0)
    return 'S';
  else if (r == 1)
    return 'A';
  else if (r == 2)
    return 'B';

  return 'e';
}


// ** Then complete the following functions.-----------------------------

// to display a rule's rhs which is in vector V
void displayVector(vector<char> V) 
{
  for (int i = 0; i < V.size(); i++)
  {
    cout << V[i] << " ";
  }
}

// to read in the rules into M, make sure ; is not stored
void readrules()
{ 
  ifstream fin ("rules", ios::in);

  // For each line of "rules" (e.g. S 0 A 0 ;)
  // The first char of a line determines the row of M
  // The second char of a line determines the column of M
  // Note that each entry of M (the second char up to ;)
  // will be a vector representing
  // the right hand side of a rule (rhs)

  char row, col;
  int r,c;
  while (fin >> row)
  {
    fin >> col;
    r = toRow(row);
    c = toCol(col);
    while (col != ';')
    {
      M[r][c].push_back(col);
      fin >> col;
    }
  }

  for (int i = 0; i < 3; i++)
  {
    cout << toNonterm(i) << ": ";
    for (int j = 0; j < 2; j++)
    {
      cout << "    ";
      if(M[i][j].size() > 0)
        displayVector(M[i][j]);

      for (int k = 0; k < (10 - (M[i][j].size() * 2) - 1); k++)
        cout << " ";
    }
    cout << endl;
  }
  fin.close();
}

//  pushes V contents to the stack 
void addtostack(vector<char> V)
{  
  for (int i = 0; i < V.size(); i++)
  {
    stack.push_back(V[i]);
  }
}

void displayStack()
{
  cout << "Stack\n";
  if (stack.size() == 0)
  {
    cout << "[ empty ]\n";
  }
  for (int i = stack.size() - 1; i >= 0; i--)
  {
    cout << stack[i] << endl;
  }
  cout << "------------\n";
}

int main()
{ 
  readrules();  // M is filled and displayed 

  string ss;
  cout << "Enter a string made of 0's and/or 1's: ";
  cin >> ss;

  stack.push_back('S');

  displayStack();
  int i = 0;  // index for ss
  int row, col;
  char topOfStack;
  while (ss[i] != '\0')  // for each char of ss
  {
    cout << "current char is: " << ss[i] << endl;
    if (stack.size() == 0)
    {
      break;
    }
    // Based on ss[i] and 
    //    the top of stack, update the stack: 
    topOfStack = stack.back();
    stack.pop_back();
    col = toCol(ss[i]);
    //checks for input that is not a 1 or 0
    if(col == -1)
      break;
    //checking to see if we need to update row
    if (topOfStack == 'S' || topOfStack == 'A' || topOfStack == 'B')
    {
      row = toRow(topOfStack);
      addtostack(M[row][col]);
      cout << "adding rhs of a rule to the stack\n\n";
      displayStack();
      continue;
    }
    //mismatch error check
    else if (topOfStack != ss[i])
    {
      break;
    }
    cout << "matched!\n\n";
    displayStack();
    i++;
  } // end of string

  cout << ">>";
  if (col == -1)
  {
    cout << "Error - no rule. Reject!\n\n";
  }
  else if (ss[i] != topOfStack && ss[i] != '\0')
  {
    cout << "Mismatch error. Reject!\n\n";
  }
  else if (stack.size() == 0 && ss[i] == '\0')
  {
    cout << "Accept!\n";
  }
  else if (stack.size() > 0)
  {
    cout << "Reject! input too short\n\n";
  }
  else if (ss[i] != '\0')
  {
    cout << "Error - stack is empty. Reject!\n\n";
  }
  cout << endl;
}// end of main
