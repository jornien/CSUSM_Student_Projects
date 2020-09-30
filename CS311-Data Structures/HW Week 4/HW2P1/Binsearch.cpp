/*===============================================
 * HW#: HW2P1 binary search
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: Binary Search implementation file
 *===============================================
*/

#include <iostream>
#include <vector>
#include "Binsearch.h"

using namespace std;

//merges two vectors into one sorted vector
vector<int> Binsearch :: combine(vector<int> left, vector<int> right)
{
  int leftI = 0;
  int rightI = 0;
  vector<int> sorted;
  while (leftI < left.size() || rightI < right.size())
  {
    if (leftI < left.size() && rightI < right.size())
    {
      if (left[leftI] < right[rightI])
      {
        sorted.push_back(left[leftI]);
        leftI++;
      }
      else
      {
        sorted.push_back(right[rightI]);
        rightI++;
      }
    }
    else if (leftI < left.size())
    {
      sorted.push_back(left[leftI]);
      leftI++;
    }
    else
    {
      sorted.push_back(right[rightI]);
      rightI++;
    }
  }

  return sorted;
}

bool Binsearch ::  binsearch(vector<int> numbers, int toFind)
{
  if (numbers.size() == 1)
  {
    return numbers[0] == toFind;
  }
  if (numbers.size() == 2)
  {
    return numbers[0] == toFind || numbers[1] == toFind;
  }
  
  vector<int> smaller;
  int middle = numbers.size() / 2;
  if (toFind == numbers[middle])
  {
    return true;
  }
  if (toFind > numbers[middle])
  {
    for (int i = middle + 1; i < numbers.size(); i++)
    {
      smaller.push_back(numbers[i]);
    }
  }
  else
  {
    for (int i = 0; i < middle; i++)
    {
      smaller.push_back(numbers[i]);
    }
  }
  return binsearch(smaller, toFind);
}

vector<int> Binsearch :: mergesort(vector<int> numbers)
{
  if (numbers.size() == 1)
  {
    return numbers;
  }
  if (numbers.size() == 2)
  {
    if (numbers[0] > numbers[1])
    {
      int temp = numbers[0];
      numbers[0] = numbers[1];
      numbers[1] = temp;
      return numbers;
    }
  }
  int middle = numbers.size() / 2;
  vector<int> left;
  vector<int> right;
  for (int i = 0; i < middle; i++)
  {
    left.push_back(numbers[i]);
  }
  for (int i = middle; i < numbers.size(); i++)
  {
    right.push_back(numbers[i]);
  }
  left = mergesort(left);
  right = mergesort(right);
  return combine(left, right);
}
