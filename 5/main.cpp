// Project 5

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
         //m.setMap(0,0,1);
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
