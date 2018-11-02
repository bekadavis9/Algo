/*
Algorithms 10/23/18
Project #3 grid.h file
Word Search
Rebekah Davis and Julian Perez
Group ID: DAVPER (24)
*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <math.h>
#include "d_matrix.h"
using namespace std;

class grid
{
  public:
    void resize();
    void setNumRows();    //user input for matrix size
    void setNumCols();
    void makeFile();      //random char generator for grid
    void fill();          //fill grid with random chars
    void wordGenerator(); //find words in grid

  private:
    int numRows;
    int numCols;
    int numChars;
    int x;                //placeholder int
    matrix <char> mat;    //matrix for grid
    vector <string> words;
};

void grid::resize()
{
  mat.resize(numRows, numCols);
}

void grid::setNumRows()
{
  cout<<"\nEnter your desired number of rows: ";
  cin>>x;
  numRows = x;
}

void grid::setNumCols()
{
  cout<<"\nEnter your desired number of columns: ";
  cin>>x;
  numCols = x;
}

//make file of random characters (lowercase letters)
void grid::makeFile()
{
  char ch;
  int x;
  unsigned seed= time(0);
  srand(seed);

  ofstream fout;
  string filename = "grid.txt"; //create output file
  fout.open(filename.c_str());

  if(!fout)
    cout<<"ERROR: could not open file."<<endl;

  else
  {
    //fout<<numRows<<" " <<numCols<<"\n";
    for(int j = 0; j<numRows; j++)
    {
      for(int k = 0; k<numCols; k++)
      {
        x = rand() % 26;    //0-26 random numbers
        ch = (char)(x+97);  //convert to ascii a-z
        fout<< ch;
      }
      fout<<"\n";
    }
  }
  fout.close(); //close output file
}

void grid::fill()
{
  char letter;
  int count = 0;
  //vector <char> filler;
  numChars = numRows * numCols;   //number of characters in grid
  char filler[numChars];


  ifstream fin;
  string filename = "grid.txt"; //open file created in makeFile()
  fin.open(filename.c_str());

  if (!fin)
  {
    cout<<"ERROR: could not open file."<<endl;
  }

  while(!fin.eof())
  {
    fin>>letter;
    filler[count] = letter;
    count++;
  }

  for(int j = 0; j < numRows; j++)
  {
    cout<<"\n";
    for(int k = 0; k < numCols; k++)
    {
        mat[j][k] = filler[j+k];
        cout<<mat[j][k];
    }
  }
	fin.close();
}

void grid::wordGenerator()
{
  int direction = 0;
  int count = 0;
  string word;
  int x, y = 0; //row, col

  ofstream fout;
  string filename = "words.txt"; //open file created in makeFile()
  fout.open(filename.c_str());

  if (!fout)
  {
    cout<<"ERROR: could not open file."<<endl;
  }

  else
  {
  	for(int j = 0; j < numCols; j++)
  	{
      direction = 0;
    	for(int k = 0; k < numRows; k++)
      {
        count = 0;
        direction++;

        switch(direction)
        {
          case 1: x = j;
          {
            word = "";
            while(count < numRows)
            {
              word += mat[x][k];
              fout<< word<< "\n";
              fout<<"k:"<<k<<"\n";
              fout<<"j:"<<j<<"\n";
              x++;
              count++;
              if(x == numRows)
                x = 0;
            }
            break;
          }


          case 2:
            y = k;
            while(count < numCols)
            {
              word += mat[j][y];
              fout<< word<< "\n";
              y++;
              count++;
              if(y == numCols)
                y = 0;
            }
            break;

          case 3:
            x = j;
            while(count < numRows)
            {
              word += mat[x][k];
              fout<< word<< "\n";
              x--;
              count++;
              if(x == -1)
                x = numRows;
            }
            break;

          case 4:
            y = k;
            while(count < numCols)
            {
              word += mat[j][y];
              fout<< word<< "\n";
              y--;
              count++;
              if(y == -1)
                y = numCols;
            }
            break;

          case 5:
            x = j;
            y = k;
            while(count < numRows)
            {
              word += mat[x][y];
              fout<< word<< "\n";
              x++;
              y++;
              count++;
              if(x == numRows)
                x = 0;
              if(y == numCols)
                y = 0;
            }
            break;

          case 6:
            x = j;
            y = k;
            while(count < numRows)
            {
              word += mat[x][y];
              fout<< word<< "\n";
              x--;
              y++;
              count++;
              if(x == -1)
                x = numRows;
              if(y == numCols)
                y = 0;
            }
            break;

          case 7:
            x = j;
            y = k;
            while(count < numRows)
            {
              word += mat[x][y];
              fout<< word<< "\n";
              x--;
              y--;
              count++;
              if(x == -1)
                x = numRows;
              if(y == -1)
                y = numCols;
            }
            break;

          case 8:
            x = j;
            y = k;
            while(count < numRows)
            {
              word += mat[x][y];
              fout<< word<< "\n";
              x++;
              y--;
              count++;
              if(x == numRows)
                x = 0;
              if(y == -1)
                y = numCols;
            }
            break;

        }
      }
    }
  }
  fout.close();
}
