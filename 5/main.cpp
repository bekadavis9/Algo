/*
Algorithms 12/5/18
Project #5 main.cpp file
Word Search
Rebekah Davis and Julian Perez
Group ID: DAVPER (24)
*/

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "main.hpp"

using namespace std;


int main()
{
   char x;
   ifstream fin;

   // Read the maze from the file.
   string fileName = "maze.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {

      graph g;
      while (fin && fin.peek() != 'Z')
      {
         maze m(fin);
         m.setVertices();
         m.findPathRecursive(0,0,9,6);
      }


   }
   catch (indexRangeError &ex)
   {
      cout << ex.what() << endl; exit(1);
   }
   catch (rangeError &ex)
   {
      cout << ex.what() << endl; exit(1);
   }
}
