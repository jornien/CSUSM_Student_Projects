/*-----------------------------------------------
 * HW#: HW4
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: binstree implementation file
 *-----------------------------------------------
*/

#include <iostream>
#include <vector>
#include "binstree.h"

using namespace std;

void binstree :: remove(node* h)
{
  if (h == NULL)
  {
    cout << "empty tree\n";
    return;
  }
  if (h -> left != NULL)
  {
    remove (h -> left);
  }
  if (h -> right != NULL)
  {
    remove (h -> right);
  }
  delete h;
}

void binstree :: insertNode(node* h, int data)
{
  if (data < h -> data)
  {
    if (h -> left == NULL)
    {
      h -> left = new node(data);
      return;
    }
    else
    {
      insertNode(h -> left, data);
    }
  }
  else if (data > h -> data)
  {
    if (h -> right == NULL)
    {
      h -> right = new node(data);
      return;
    }
    else
    {
      insertNode(h -> right, data);
    }
  }
  else
  {
    cout << "data already in tree\n";
  }
}

void binstree :: insertNode(int data)
{
  if (head == NULL)
  {
    head = new node(data);
    return;
  }
  else
  {
    insertNode(head, data);
  }
}

void binstree :: deleteNode(int data)
{
  if (!isInTree(data))
  {
    cout << data << " is not in tree\n";
    return;
  }
  balanceTree(data);
}

bool binstree :: isInTree(int d)
{
  node* scanner = head;
  while (scanner != NULL)
  {
    if (scanner -> data == d)
    {
      return true;
    }
    else if (scanner -> data > d)
    {
      scanner = scanner -> left;
    }
    else
    {
      scanner = scanner -> right;
    }
  }
  return false;
}

void binstree :: PreOrder(node* h)
{
  if (h == NULL)
  {
    cout << "empty tree\n";
    return;
  }
  cout << h -> data << endl;
  if (h -> left != NULL)
  {
    PreOrder(h -> left);
  }
  if (h -> right != NULL)
  {
    PreOrder(h -> right);
  }
}

void binstree :: InOrder(node* h)
{
  if (h == NULL)
  {
    cout << "empty tree\n";
    return;
  }
  if (h -> left != NULL)
  {
    InOrder(h -> left);
  }
  cout << h -> data << endl;
  if (h -> right != NULL)
  {
    InOrder(h -> right);
  }
}

void binstree :: PostOrder(node* h)
{
  if (h == NULL)
  {
    cout << "empty tree\n";
    return;
  }
  if (h -> left != NULL)
  {
    PostOrder(h -> left);
  }
  if (h -> right != NULL)
  {
    PostOrder(h -> right);
  }
  cout << h -> data << endl;
}

void binstree :: balanceTree()
{
  if (head == NULL)
  {
    cout << "empty tree\n";
    return;
  }
  vector<node*> nodes;
  vector<int> sorted;
  nodes.push_back(head);
  int i = 0;
  while (i < nodes.size())
  {
    if (nodes[i] -> left != NULL)
    {
      nodes.push_back(nodes[i] -> left);
    }
    if (nodes[i] -> right != NULL)
    {
      nodes.push_back(nodes[i] -> right);
    }
    i++;
  }
  sorted = sortData(nodes);
  remove(head);
  head = NULL;
  makeTree(sorted);
}

void binstree :: balanceTree(int toDelete)
{
  if (head == NULL)
  {
    cout << "empty tree\n";
    return;
  }
  vector <node*> nodes;
  vector <int> sorted;
  nodes.push_back(head);
  int i = 0;
  while(i < nodes.size())
  {
    if (nodes[i] -> left != NULL)
    {
      nodes.push_back(nodes[i] -> left);
    }
    if (nodes[i] -> right != NULL)
    {
      nodes.push_back(nodes[i] -> right);
    }
    i++;
  }
  sorted = sortData(nodes, toDelete);
  remove(head);
  head = NULL;
  makeTree(sorted);
}

vector<int> binstree :: sortData(vector<node*> nodes, int toDelete)
{
  vector<int> sorted;
  int smallest;
  while (!nodes.empty())
  {
    smallest = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
      if (nodes[smallest] -> data > nodes[i] -> data)
      {
        smallest = i;
      }
    }
    if (nodes[smallest] -> data != toDelete)
    {
      sorted.push_back(nodes[smallest] -> data);
    }
    nodes.erase(nodes.begin() + smallest);
  }
  return sorted;
}

vector<int> binstree :: sortData(vector<node*> nodes)
{
  vector<int> sorted;
  int smallest;
  while (!nodes.empty())
  {
    smallest = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
      if (nodes[smallest] -> data > nodes[i] -> data)
      {
	smallest = i;
      }
    }
    sorted.push_back(nodes[smallest] -> data);
    nodes.erase(nodes.begin() + smallest);
  }
  return sorted;
}

void binstree :: makeTree(vector<int> sorted)
{
  if (sorted.size() == 1)
  {
    insertNode(sorted[0]);
    return;
  }
  if (sorted.size() == 2)
  {
    insertNode(sorted[0]);
    insertNode(sorted[1]);
    return;
  }
  vector<int> left;
  vector<int> right;
  int middle = sorted.size() / 2;
  insertNode(sorted[middle]);
  for (int i = 0; i < middle; i++)
  {
    left.push_back(sorted[i]);
  }
  for (int i = middle + 1; i < sorted.size(); i++)
  {
    right.push_back(sorted[i]);
  }
  makeTree(left);
  makeTree(right);
}
