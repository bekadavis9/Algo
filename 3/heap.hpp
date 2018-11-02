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
#include <algorithm>
#include <math.h>
using namespace std;

#ifndef HEAP_H
#define HEAP_H

template <typename T>
class heap
{
  public:
	int parent(vector <T> &v);
    int left(vector <T> &v);
    int right(vector <T> &v);
    int getItem(vector <T> &v, int n);
    void initializeMaxHeap();
    void maxHeapify();
    void buildMaxHeap();
    void heapSort();

  private:
    vector <T> v;
    int length;
    int parent;
    int left;
    int right;

  };
  #endif

int heap::parent(&v)
{
  length = v.size();
  int p_index = floor(length/2);
  parent = getItem(v, p_index);
  return parent;
}

int heap::left(&v)
{
  length = v.size();
  int l_index = 2 * length;
  left = getItem(v, l_index);
  return left;
}

int heap::right(&v)
{
  length = v.size();
  int r_index = 2 * length + 1;
  right = getItem(v, r_index);
  return right;
}

int heap::getItem(&v, int n)
{
  string tmp;
  length = v.size();
  for(int i = 0; i<length; i++)
  {
    tmp = v[i];
    if(tmp == n)
      return i;
  }
  return -1;
}

void heap::initializeMaxHeap(&v)
{
  parent = v.parent();
  left = v.left();
  right = v.right();
}

void heap::maxHeapify(std::vector<string>& v, int n)
{
  int max;

  if( left < v.size() && v[left] > v[n])
    max = left;

  else
    max = n;

  if( right < v.size() && v[right] > v[max])
    max = right;

  if( max != n)
  {
      std::swap(v[n], v[max]);
      max_heapify(v,max);
  }
}

void heap::buildMaxHeap(std::vector<string>& v)
{
  for(int i = v.size() - 2; i >= 0; --i)
  {
      max_heapify(v, i);
  }
}

void heap::heapSort(std::vector<string>& v)
{
  build_max_heap(v);
  int x = 0;
  int i = v.size() - 1;
  while( i > x)
  {
      std::swap(v[i],v[x]);
      ++x;
      --i;
  }
}
