#include<iostream>
#include<string>
#include <fstream>
using namespace std;

//-------------------------------------------------------
// CS421 HW1 
// Write a recognizer in C++ for L = {x | x is a binary number}.
// Your name: Jordan Nienaber
// To run: g++ recognizer.cpp
//-------------------------------------------------------

//  The recognizer function should return TRUE or FALSE 
//  checking each character
//  to make sure it is 0 or 1. (leading 0's are allowed).
bool recognizer(string s)
{ 
  for (int i = 0; i < s.length(); i++)
  {
    if(s[i] != '0' && s[i] != '1')
      return false;
  }
  return true;
}// end of recognizer

//main: Given a string (from E) cined from the user, pass it to
//      the recognizer function.
//      Cout "YES IN L" or "NO NOT IN L" depending on what was returned.
int main()
{
  ofstream file;
  file.open("Routput.txt");
  string input = "";
  //Loop runs until no or No is input
  while (input.compare("no") != 0 && input.compare("No") != 0)
  {
    cout << "Enter a sequence of numbers to determine if it is binary: ";
    getline(cin, input);
    file << input;
    if (recognizer(input))
    {
      cout << "YES IN L\n";
      file << " YES IN L\n";
    }
    else
    {
      cout << "NO NOT IN L\n";
      file << " NO NOT IN L\n";
    }
    cout << "enter another number? ";
    getline(cin, input);
  }
  file.close();

}// end of main
