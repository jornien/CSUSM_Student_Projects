#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//----------------------------------------------
// CS421 HW1 
// Write a generator in C++ for L = {x | x is a binary number}.
// Your name: Jordan Nienaber
// To compile: g++ generator.cpp
//----------------------------------------------

//Returns true if the string is nothing but 1's and 0's
//Returns false if any other char is in the string
bool recognizer(string s)
{
  for (int i = 0; i < s.length(); i++)
  {
    if(s[i] != '0' && s[i] != '1')
      return false;
  }
  return true;
}


// main: It should create each string over E = {0,1,2} systematically
//   (short to long) and pass each string to the recognizer function
//   created in Part a).  Hint: use a queue to generate strings
//   Only those strings for which the recognizer returned TRUE
//   should be displayed. 
//   Keeps on going until the queue overflows but the user can 
//   terminate the program with control-C 
//   after about 20 strings have been displayed.
int main()
{ 
  string output = "0";
  ofstream file;
  file.open("Goutput.txt");
  int canExit = 0;
  //Generates 20 binary numbers then terminates
  while (canExit < 20)
  {
    if(recognizer(output))
    {
      cout << output << endl;
      file << output << endl;
      canExit++;
    }
    for (int i = output.length() - 1; i >= 0; i--)
    {
      if(output[i] == '0')
      {
        output[i] = '1';
	break;
      }
      if(output[i] == '1')
      {
	output[i] = '2';
	break;
      }
      if(output[i] == '2')
      {
	output[i] = '0';
	//Checks to see if we've hit the end of the string
	//If we have, then we add a 0 to thr front of the string
	//Otherwise, we still have more digits in the string to check
	if(i == 0)
	{
	  output = "0" + output;
	  break;
	}
      }
    }
  }
  file.close();
}
