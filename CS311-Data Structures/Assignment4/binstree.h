/*-----------------------------------------------
 * HW#: HW4
 * Name: Jordan Nienaber
 * Compiler: g++
 * File Type: binstree header file
 *-----------------------------------------------
*/

#include <iostream>
#include<vector>

using namespace std;

class binstree
{
  class node
  {
    public:
      int data;
      node* left;
      node* right;
      node (int d) {data = d; left = right = NULL;};
      void remove() {delete left; delete right;};
  };

  private:
    node* head;
    void insertNode(node* h, int data);
    void balanceTree(int toDelete);
    void remove(node* h);
    void PreOrder(node* h);
    void InOrder (node* h);
    void PostOrder (node* h);
    vector<int> sortData(vector<node*> nodes);
    vector<int> sortData(vector<node*> nodes, int toDelete);
  public:
    binstree() {head = NULL;};
    binstree(int data) {head = new node(data);};
    void insertNode(int data);
    void deleteNode(int data);
    void balanceTree();
    void makeTree(vector<int> data);
    bool isInTree(int data);
    void remove() {remove(head);};
    void PreOrder() {PreOrder(head);};
    void InOrder() {InOrder(head);};
    void PostOrder() {PostOrder(head);};
};
