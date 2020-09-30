#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 18 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Jordan Nienaber
// RE: { (vowel | (vowel n) | (consonant vowel) | (consonant vowel n) | (consonant-pair vowel) 
// 	 | (consonant-pair vowel n))^n | n >= 1}
bool word (string s)
{

  int state = 0;
  for (int i = 0; i < s.length(); i++)
  {
    if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o'
	|| s[i] == 'u' || s[i] == 'I' || s[i] == 'E' || s[i] == 'n')
    {
      //Only state 5 can't be proceeded by a vowel or n, so we must check
      if (state != 5)
        state = 0;
    }
    //Checks all non-vowel paths from state 0
    else if (state == 0)
    {
      if (s[i] == 'd' || s[i] == 'w' || s[i] == 'z' || s[i] == 'y' 
	|| s[i] == 'j')
      {
	state = 1;
      }
      else if (s[i] == 'b' || s[i] == 'm' || s[i] == 'k' || s[i] == 'h' 
	|| s[i] == 'p' || s[i] == 'r' || s[i] == 'g')
      {
	state = 2;
      }
      else if (s[i] == 't')
      {
	state = 3;
      }
      else if (s[i] == 's')
      {
        state = 4;
      }
      else if (s[i] = 'c')
      {
        state = 5;
      }
    }
    //Checks each consonant pair
    else if ((state == 2 && s[i] == 'y') || (state == 3 && s[i] == 's')
	|| ((state == 4 || state == 5) && s[i] == 'h'))
    {
	state = 0;
    }
    else
    {
      return false;
    }
  }
  //state 0 is the final state
  return state == 0;
}

// PERIOD DFA 
// Done by: Jordan Nienaber
bool period (string s)
{
  if(s.length() == 1)
  {
    return (s[0] == '.');
  }
  return false;
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Jordan Nienaber

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, EOFM, VERB, VERBNEG, VERBPAST,
	VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", "VERB",
	"VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT",
	"DESTINATION", "PRONOUN", "CONNECTOR"}; 

string reservedWords[19] = {"masu", "masen", "mashita", "masendeshita", "desu",
	"deshita", "o", "wa", "ni", "watashi", "anata", "kare", "kanojo", "sore",
	"mata", "soshite", "shikashi", "dakara", "eofm"};
// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.


// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Jordan Nienaber
int scanner(tokentype& tt, string& w)
{
  fin >> w;
  if (w == "eofm")
  {
    tt = EOFM;
  }
  else if (word(w))
  {
    for (int i = 0; i < 19; i++)
    {
      if (w == reservedWords[i])
      {
	if (i == 0)
	  tt = VERB;
	else if (i == 1)
	  tt = VERBNEG;
	else if (i == 2)
	  tt = VERBPAST;
	else if (i == 3)
	  tt = VERBPASTNEG;
	else if (i == 4)
	  tt = IS;
	else if (i == 5)
	  tt = WAS;
	else if (i == 6)
	  tt = OBJECT;
	else if (i == 7)
	  tt = SUBJECT;
	else if (i == 8)
	  tt = DESTINATION;
	else if (i >= 9 && i <= 13)
	  tt = PRONOUN;
	else if (i >= 14 && i <= 18)
	  tt = CONNECTOR;
	return -1;
      }
    }
    if (w[w.length() -1] == 'E' || w[w.length() - 1] == 'I')
    {
      tt = WORD2;
    }
    else
    {
      tt = WORD1;
    }
  }
  else if (period(w))
  {
    tt = PERIOD;
  }
  else
  {
    cout << "Lexical Error: " << w << " is not a valid token\n";
    tt = ERROR;
  }  
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Rika
int main()
{
  tokentype thetype;
  string theword; 
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
  while (true)
  {
    scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments  
    if (theword == "eofm") break;  // stop now

    cout << "Type is:" << tokenName[thetype] << endl;
    cout << "Word is:" << theword << endl << endl;
  }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end

