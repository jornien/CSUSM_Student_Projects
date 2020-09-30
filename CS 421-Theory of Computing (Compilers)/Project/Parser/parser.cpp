#include<iostream>
#include<fstream>
#include<string>
#include <stdlib.h>
using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: **
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: ** 


// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: ** 
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: ** 

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.

//=================================================
// File parser.cpp written by Group Number: 18
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// TABLES Done by: Jordan Nienaber
// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum token_type {ERROR, WORD1, WORD2, PERIOD, EOFM, VERB, VERBNEG, VERBPAST,
	VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR};
	
// ** For the display names of tokens - must be in the same order as the tokentype.
string token_name[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", "VERB",
	"VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT",
	"DESTINATION", "PRONOUN", "CONNECTOR"};

string reservedWords[19] = {"masu", "masen", "mashita", "masendeshita", "desu",
	"deshita", "o", "wa", "ni", "watashi", "anata", "kare", "kanojo", "sore",
	"mata", "soshite", "shikashi", "dakara", "eofm"};

token_type saved_token;
token_type next_token_val;
bool token_available;
string saved_lexeme;
ifstream fin; // global stream for reading from the input file
ofstream errorfile;

//function prototypes
bool syntaxerror1(token_type nextT, token_type expected);
void syntaxerror2(string, string);
token_type next_token();
bool match(token_type expected);
bool word_token(string s);
bool period_token(string s);
int scanner(token_type& tt, string& w);
void story();
void S();
void after_subject();
void after_noun();
void after_object();
void verb();
void noun();
void be();
void tense();

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: Syntactical
// Done by: Erik Shepard
bool syntaxerror1(token_type nextT, token_type expected){
  cout <<"SYNTAX ERROR: Expected " <<token_name[expected] <<" but found " << saved_lexeme <<endl;
  exit(1);
}
// Type of error: Lexical
// Done by: Erik Shepard
void syntaxerror2(string s_lex, string func_name) {
  cout <<"SYNTAX ERROR: Unexpected " <<s_lex <<" found in " <<func_name <<endl;
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: **
// Done by: Erik Shepard
token_type next_token(){
  if (!token_available) {
    scanner(saved_token, saved_lexeme);
    token_available = true;
  }
  return saved_token;
}

// Purpose: **
// Done by: Erik Shepard
bool match(token_type expected) {
  next_token_val = next_token();
  if(next_token_val != expected)
    return syntaxerror1(next_token_val, expected);
  else {
    cout <<"Matched " <<token_name[expected] <<endl;
    token_available = false;
    return true;
  }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: **
// Done by: Erik Shepard

void story() {
  cout << "Processing <story>" << endl << endl;
  S();
  while (true) {
    switch(next_token()) {
    case CONNECTOR: 
      S(); 
      break;
    case WORD1: 
      S(); 
      break;
    case PRONOUN: 
      S(); 
      break;
    case EOFM: 
      return;
    default: 
      syntaxerror2(saved_lexeme, "story"); 
      return;
    }
  }
}

void S() {
  cout << "Processing <S>" << endl;
  if (next_token() == CONNECTOR) {
    match(CONNECTOR);
  }
  noun();
  match(SUBJECT);
  after_subject();
}

void after_subject() {
  cout << "Processing <after_subject>" << endl;
  switch(next_token()) {
  case WORD2: 
    verb(); 
    tense(); 
    match(PERIOD); 
    break;
  case WORD1: 
    noun(); 
    after_noun(); 
    break;
  case PRONOUN: 
    noun(); 
    after_noun; 
    break;
  default: 
    syntaxerror2(saved_lexeme, "after_subject");
  }
  
}

void after_noun() {
  cout << "Processing <after_noun>" << endl;
  switch(next_token()) {
  case IS: 
    be(); 
    match(PERIOD); 
    break;
  case WAS: 
    be(); 
    match(PERIOD); 
    break;
  case DESTINATION: 
    match(DESTINATION); 
    verb(); 
    tense(); 
    match(PERIOD); 
    break;
  case OBJECT: 
    match(OBJECT); 
    after_object(); 
    break;
  default: syntaxerror2(saved_lexeme, "after_noun");
    
  }
}

void after_object() {
  cout << "Processing <after_object>" << endl;
  switch(next_token()) {
  case WORD2: 
	verb(); 
	tense(); 
	match(PERIOD); 
	break;
  case WORD1: 
	noun(); 
	match(DESTINATION); 
	verb(); 
	tense(); 
	match(PERIOD); 
	break;
  case PRONOUN: 
	noun(); 
	match(DESTINATION); 
	verb(); 
	tense(); 
	match(PERIOD); 
	break;
  default: syntaxerror2(saved_lexeme, "after_object");
  }
}

void noun() {
  cout << "Processing <noun>" << endl;
  switch(next_token()) {
  case WORD1: 
    match(WORD1); 
    break;
  case PRONOUN: 
    match(PRONOUN); 
    break;
  default: 
    syntaxerror2(saved_lexeme, "noun");
  }
}

void verb() {
  cout << "Processing <verb>" << endl;
  match(WORD2);
}

void be() {
  cout << "Processing <be>" << endl;
  switch(next_token()) {
  case IS: 
    match(IS); 
    break;
  case WAS: 
    match(WAS); 
    break;
  default: syntaxerror2(saved_lexeme, "be");
  }
}

void tense() {
  cout << "Processing <tense>" << endl;
  switch(next_token()) {
  case VERBPAST: 
    match(VERBPAST); 
    break;
  case VERBPASTNEG: 
    match(VERBPASTNEG); 
    break;
  case VERB: 
    match(VERB); 
    break;
  case VERBNEG: 
    match(VERBNEG); 
    break;
  default: syntaxerror2(saved_lexeme, "tense");
  }
  
}
//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  Erik Shepard
int main()
{

  //** opens the lexicon.txt file and reads it into Lexicon
  //** closes lexicon.txt 

  //** opens the output file translated.txt

  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  //** closes the input file 
  cout <<"End of file is encountered\n";
  cout <<"Successfully parsed <story>\n";
  fin.close();

  //** closes the input file 
  //** closes traslated.txt

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

// Scanner Functions
// WORD DFA 
// Done by: Jordan Nienaber
// RE: { (vowel | (vowel n) | (consonant vowel) | (consonant vowel n) | (consonant-pair vowel) 
// 	 | (consonant-pair vowel n))^n | n >= 1}
bool word (string s)
{

  int state = 0;
  for (int i = 0; i < s.length(); i++)
  {
    if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'I' || s[i] == 'E' || s[i] == 'n')
    {
      //Only state 5 can't be proceeded by a vowel or n, so we must check
      if (state != 5)
        state = 0;
    }
    //Checks all non-vowel paths from state 0
    else if (state == 0)
    {
      if (s[i] == 'd' || s[i] == 'w' || s[i] == 'z' || s[i] == 'y' || s[i] == 'j')
      {
	state = 1;
      }
      else if (s[i] == 'b' || s[i] == 'm' || s[i] == 'k' || s[i] == 'h' || s[i] == 'p' || s[i] == 'r' || s[i] == 'g')
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
    else if ((state == 2 && s[i] == 'y') || (state == 3 && s[i] == 's')|| ((state == 4 || state == 5) && s[i] == 'h'))
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
// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Jordan Nienaber
int scanner(token_type& tt, string& w)
{
  fin >> w;
  cout << "Scanner called using word: " << w << endl;
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
/*
int scanner(token_type& a, string& w)
{

  // ** Grab the next word from the file via fin
  fin >> w; 
  cout << "Scanner called using word: " << w << endl; 
  /* 
  2. Call the token functions one after another (if-then-else)
     And generate a lexical error message if both DFAs failed.
     Let the token_type be ERROR in that case.
  3. Make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.
  4. Return the token type & string  (pass by reference)
  
  if (word(w)) {
    it = reservedWords.find(w);
    if (it != reservedWords.end()) {
      a = it->second;
    } else if (w.back() == 'I' || w.back() == 'E') {
      a = WORD2;
    } else {
      a = WORD1;
    }
  } else if (period(w)) {
    a = PERIOD;
  } else {
    if (w != "eofm") {
      cout << "Lexical Error: " << w << " is not a valid token" << endl;
      a = ERROR;
    } else {
      a = EOFM;
    }
  }

}//the end of scanner
*/
// DO WE NEED THIS?
/*
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

*/
