/*
Algorithms 10/23/18
Project #3 main.cpp file
Word Search
Rebekah Davis and Julian Perez
Group ID: DAVPER (24)
*/

#include <stdlib.h>
#include <iostream>
#include "dictionary.h"
using namespace std;

int main()
{
  grid g;

  g.setNumRows();
  g.setNumCols();
  g.resize();
  g.makeFile();
  g.fill();
  g.wordGenerator();


  //dictionary d;
  //d.selectionSort();

  //d.binarySearch("a");

  return 0;
}
