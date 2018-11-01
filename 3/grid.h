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
  vector <char> filler;
  numChars = numRows * numCols;   //number of characters in grid

  ifstream fin;
  string filename = "grid.txt"; //open file created in makeFile()
  fin.open(filename.c_str());

  if (!fin)
  {
    cout<<"ERROR: could not open file."<<endl;
  }

  while(!fin.eof())
  {
    for(int j = 0; j < numRows-1; j++)
  	{
      cout<<"\n";
  		for(int k = 0; k < numCols; k++)
  		{
        fin>>mat[j][k];
        cout<<mat[j][k];
      }
    }
  }
	fin.close();
}

void grid::wordGenerator()
{
	numChars = numRows * numCols;
  int direction = 0;
	string word;
  int back_j, back_k;

  ofstream fout;
  string filename = "words.txt"; //open file created in makeFile()
  fout.open(filename.c_str());

  if (!fout)
  {
    cout<<"ERROR: could not open file."<<endl;
  }

  else
  {
    while(numChars > 0)
    {
  		for(int j = 0; j < numRows; j++)
    	{
        direction = 0;
      	for(int k = 0; k < numCols; k++)
  	    {
          back_j = j-1;
          back_k = k-1;
          if (j == -1)
          {
            j = numRows - 1;
            continue;
          }
          else if(j == numRows)
          {
            j = 0;
            continue;
          }
          else if(k == -1)
          {
            k = numRows - 1;
            continue;
          }
          else if(k == numCols)
          {
            k = 0;
            continue;
          }

          //gridWords.push_back(word);
          fout<<word;
          fout<<"\n";
          direction++;

          switch(direction)
          {
            case 1:
              word += mat[j][k];
              continue;
            case 2:
              word += mat[j][k+1];
              continue;
            case 3:
              word += mat[j+1][k+1];
              continue;
            case 4:
              word += mat[j+1][k];
              continue;
            case 5:
              word += mat[j+1][back_k];
              continue;
            case 6:
              word += mat[j][back_k];
              continue;
            case 7:
              word += mat[back_j][back_k];
              continue;
            case 8:
              word += mat[back_j][k];
              continue;
            case 9:
              word += mat[back_j][k+1];
              continue;
          }
       }

	 }
   numChars--;
   }
 }
 fout.close();
}
