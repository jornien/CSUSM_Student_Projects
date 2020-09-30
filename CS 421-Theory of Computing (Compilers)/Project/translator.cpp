#include<iostream>
#include<fstream>
#include<string>
#include <stdlib.h>
#include <vector>
using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
         cp ../ParserFiles/parser.cpp .
	    Then, insert or append its contents into this file and edit.
	       Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: 18
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt
//  Done by: Jordan Nienaber

class Translation
{
private:
  string english;
  string japanese;
public:
  Translation() {english = ""; japanese = ""; };
  Translation(string e, string j)
  {
    english = e;
    japanese = j;
  }

  void setEnglish(string e) {english = e; };
  void setJapanese(string j) {japanese = j; };
  string getEnglish() {return english; };
  string getJapanese() { return japanese; };

  int compare(Translation t)
  {
    int min, toReturn;
    if (t.getJapanese().size() > japanese.size())
      {
	min = japanese.size();
	toReturn = 1;
      }
    else
      {
	min = t.getJapanese().size();
	if (t.getJapanese().size() == japanese.size())
	  toReturn = 0;
	else
	  toReturn = -1;
      }
    for (int i = 0; i < min; i++)
      {
	//If t has a word later in the alphabet, returns 1 to move right
	if (t.getJapanese()[i] > japanese[i])
	  return 1;
	//IF t has a word earlier in the alphabet, returns -1 to move left
	else if (t.getJapanese()[i] < japanese[i])
	  return -1;
      }
    //If here, either the words are the same
    //Or the share all the same letters but one is longer
    return toReturn;
  }
};

vector<Translation> lexicon;

//Reads from lexicon.txt and creates the dictionary
void readLexicon()
{
  vector<Translation>::iterator it;
  int index;
  Translation t;
  ifstream lfin;
  lfin.open("lexicon.txt");
  string japanese, english;

  lfin >> japanese;
  lfin >> english;
  t.setEnglish(english);
  t.setJapanese(japanese);

  lexicon.push_back(t);

  while (lfin >> japanese)
    {
      lfin >> english;
      t.setEnglish(english);
      t.setJapanese(japanese);

      for (it = lexicon.begin(), index = 0; index < lexicon.size(); it++, index++)
	{
	  if(t.compare(lexicon[index]) >= 0)
	    break;
	}
      if(index == lexicon.size())
	{
	  lexicon.push_back(t);
	  continue;
	}
      lexicon.insert(it, t);
    }

  lfin.close();
}

// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result
//                 in saved_E_word
//  Done by: Jordan Nienaber

//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: Erik Shepard

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
string saved_E_word;
ifstream fin; // global stream for reading from the input file
ofstream fout; // global stream for outputing to the translated file
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
void getEword();
void gen(string line_type);
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
  fout << "\n";
  if (next_token() == CONNECTOR) {
    match(CONNECTOR);
    getEword();
    gen("CONNECTOR");
  }
  noun();
  match(SUBJECT);
  gen("ACTOR");
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
    gen("TO");
    verb();
    tense();
    match(PERIOD);
    break;
  case OBJECT:
    match(OBJECT);
    gen("OBJECT");
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
    gen("TO");
    verb();
    tense();
    match(PERIOD);
    break;
  case PRONOUN:
    noun();
    match(DESTINATION);
    gen("TO");
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
    getEword();
    match(WORD1);
    break;
  case PRONOUN:
    getEword();
    match(PRONOUN);
    break;
  default:
    syntaxerror2(saved_lexeme, "noun");
  }
}

void verb() {
  cout << "Processing <verb>" << endl;

  if( match(WORD2) ) {
    getEword();
    gen("ACTION");
  }
  else
    syntaxerror2(saved_lexeme, "verb");
}

void be() {
  cout << "Processing <be>" << endl;
  gen("DESCRIPTION");
  switch(next_token()) {
  case IS:
    match(IS);
    gen("TENSE");
    break;
  case WAS:
    match(WAS);
    gen("TENSE");
    break;
  default: syntaxerror2(saved_lexeme, "be");
  }
}

void tense() {
  cout << "Processing <tense>" << endl;
  switch(next_token()) {
  case VERBPAST:
    match(VERBPAST);
gen("TENSE");
    break;
  case VERBPASTNEG:
    match(VERBPASTNEG);
gen("TENSE");
    break;
  case VERB:
    match(VERB);
gen("TENSE");
    break;
  case VERBNEG:
    match(VERBNEG);
gen("TENSE");
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
  readLexicon();

  //** opens the output file Translationlated.txt
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());
  fout.open("translated.txt");

  //** calls the <story> to start parsing
  story();

  //** closes the input file
  cout <<"End of file is encountered\n";
  cout <<"Successfully parsed <story>\n";
  fin.close();

  //** closes traslated.txt
  fout.close();

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

// Scanner Functions
// WORD DFA
// Done by: Jordan Nienaber
// RE: { (vowel | (vowel n) | (consonant vowel) | (consonant vowel n) | (consonant-pair vowel)
//  | (consonant-pair vowel n))^n | n >= 1}
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

//Conducts a binary search to quickly find a word if it exists in the lexicon
//Done by: Jordan Nienaber
int search(Translation t, int start, int end)
{
  //if down to two or one elements
  if(end - start <= 1)
    {
      if(t.compare(lexicon[start]) == 0)
	return start;
      else if (t.compare(lexicon[end]) == 0)
	return end;
      else
	return -1;
    }

  int mid = (end + start) / 2;

  if (t.compare(lexicon[mid]) == 0)
    return mid;
  else if (t.compare(lexicon[mid]) > 0)
    return search(t, start, mid);
  else
    return search(t, mid, end);
}

//    getEword() - using the current saved_lexeme, look up the English word
//       in Lexicon if it is there -- save the result
//       is saved_E_word
//  Done By: Jordan Nienaber
void getEword()
{
  Translation t("", saved_lexeme);
  int index = search(t, 0, lexicon.size());
  if(index == -1)
    saved_E_word = saved_lexeme;
  else
    saved_E_word = lexicon[index].getEnglish();

}

//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: Erik Shepard
void gen(string line_type)
{
  if(line_type == "TENSE") {
    fout <<line_type <<": " <<token_name[saved_token] <<"\n";
  }
  else {
    fout <<line_type <<": " <<saved_E_word <<"\n";
  }
}
