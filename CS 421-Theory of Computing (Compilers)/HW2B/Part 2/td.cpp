#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

//--------------------------------------
// CS421 File td.cpp for HW2B Table-Driven Scanner
// Your name: Jordan Nienaber
//--------------------------------------

// Complete this to fit the HW2B specification - look for **
// Must have the same types of tracing couts as my demo program.


// info on each DFA
struct info
{
  string name;  // token name
  int startstate;
  int finalstate;
};

info DFAs[4];     // store up to 4 dfas' start and final

int  TRS[10][4];  // store all trs's - states 0-9 and chars a b c d -- all dfas transitions are in here 

// ----- utility functions -----------------------

int readTables()
{  
  int dfaCounter = 0;
  ifstream fin ("trs.txt", ios::in);
  ifstream fin2 ("dfas.txt", ios::in);
  for(int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      fin >> TRS[i][j];
    }
  }
  fin.close();
  
  //Runs until the fin2 runs out of DFAs to read
  while (fin2 >> DFAs[dfaCounter].name)
  {
    fin2 >> DFAs[dfaCounter].startstate;
    fin2 >> DFAs[dfaCounter].finalstate;
    dfaCounter++;
  }
  fin2.close();
  return dfaCounter;
}

void displayTables(int numDFAs)
{
  cout << "States are 0 to 9 and chars are a to d\n";
  cout << "        a b c d\n";
  for (int i = 0; i < 10; i++)
  {
    cout << "State " << i << ":";
    for (int j = 0; j < 4; j++)
    {
      if(TRS[i][j] != -1)
	cout << TRS[i][j] << " ";
      else
	cout << "  ";
    }
    cout << endl;
  }
  for (int i = 0; i < numDFAs; i++)
  {
    cout << DFAs[i].name << ": " << DFAs[i].startstate 
      << " is start and ends in " << DFAs[i].finalstate << endl;
  }
}

bool accept(info dfa, string word)
{
  int minVal = 97;
  int col;
  int row = dfa.startstate;
  for (int i = 0; i < word.length(); i++)
  {
    col = (int)word[i] - minVal;
    cout << "state: " << row << " char: " << word[i] << endl;
    row = TRS[row][col];
    cout << "new state: " << row << endl;
    if (row == -1)
      return false;
  }
  return true;
}


int main()
{
  cout << "This is a table driven scanner. Needs trs.txt and dfas.txt." << endl;
  cout << "States are 0 to 9 and chars are a to d" << endl;

  int numDFA = readTables(); // how many DFAs were read
  displayTables(numDFA);     // DISPLAY TABLES
  cout << ".....done reading tables...." << endl;

  string word;
  bool accepted;
  while(true)
  { 
    accepted = false;
    cout << "@@Enter a string: " ;
    cin >> word;
    for (int i = 0; i < numDFA; i++)
    {
      cout << "Trying dfa " << i << "--------\n";
      if (accept(DFAs[i], word))
      {
        accepted = true;
	cout << "found token " << DFAs[i].name << endl;
	break;
      }
    }
    if (!accepted)
      cout << "Lexical error!\n";

    cout << "do control-C to quit" << endl;
  }

}//the end
