/*
Algorithms 10/23/18
Project #3 dictionary.h file
Word Search
Rebekah Davis and Julian Perez
Group ID: DAVPER (24)
*/

#include <stdlib.h>
#include <iostream>
#include <random>
#include "grid.h"
using namespace std;

#ifndef HEAP_H
#define HEAP_H

template <typename T>
class node
{
   public:
      T nodeValue;      // data held by the node
      node<T> *next;    // next node in the list

      // default constructor with no initial value
      node() : next(NULL)
      {}

      // constructor. initialize nodeValue and next
      node(const T& item, node<T> *nextNode = NULL) :
			  nodeValue(item), next(nextNode)
      {}
};

#endif   // NODE_CLASS

template <typename T>
class heap
{
	public:
		int parent(vector <T> &v);
    int left(vector <T> &v);
    int right(vector <T> &v);
    int getItem(vector <T> &v, int n);
