/*
Algorithms 11/5/18
Project #4 board.h file
Word Search
Rebekah Davis and Julian Perez
Group ID: DAVPER (24)
*/

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include <vector>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

class board
// Stores the entire Sudoku board
{
	public:
    	board(int);
    	void clear();
    	void setCell(int row, int col, int digit);
    	void initialize(ifstream &fin);
    	void print();
    	bool isBlank(int, int);
		ValueType getCell(int, int);
		void DigitsInRow(int row);
		void DigitsInCol(int col);
		void DigitsInSquare(int row, int col);
    	void printConflicts();

	private:
    	matrix<ValueType> value;
    	int numRows = 9;
    	int numCols = 9;
    	int numSquares = 9;
    	int numDigits = 9;
		//matrix <vector<bool> > *conflicts(int numRows, int numCols);
    	int rowDigits[9];
    	int colDigits[9];
    	int sqDigits[9];
};

board::board(int sqSize)
	: value(BoardSize+1,BoardSize+1)
// Board constructor
{
	clear();
}

void board::clear()
// Mark all possible values as legal for each board entry
{
	for (int i = 1; i <= BoardSize; i++)
	{
    	for (int j = 1; j <= BoardSize; j++)
    	{
        	value[i][j] = Blank;
    	}
	}
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
	char ch;
	clear();
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
    		fin >> ch;
        	// If the read char is not Blank
      		if (ch != '.')
      		{
           		setCell(i,j,ch-'0');   // Convert char to int
           	}
		}
	}
}

void board::setCell(int row, int col, int digit)
{
	value[row][col] = digit;
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
   // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
   // coordinates of the square that i,j is in.

	return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
	for (int i = 0; i < v.size(); i++)
	{
    	ostr << v[i] << " ";
	}
	
	cout << endl;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
	{
		return value[i][j];
	}
	else
	{
    	throw rangeError("bad value in getCell");
  	}
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
	if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
	{
    	throw rangeError("bad value in setCell");
    }

	return (getCell(i,j) == Blank);
}

void board::print()
// Prints the current board.
{
	for (int i = 1; i <= BoardSize; i++)
	{
    	if ((i-1) % SquareSize == 0)
    	{
        	cout << " -";
			for (int j = 1; j <= BoardSize; j++)
			{
	    		cout << "---";
         		cout << "-";
         	}
	 		cout << endl;
    	}
	for (int j = 1; j <= BoardSize; j++)
    {
		if ((j-1) % SquareSize == 0)
		{
	    	cout << "|";
	    }
	 	
		if (!isBlank(i,j))
	 	{
	    	cout << " " << getCell(i,j) << " ";
		}
	 	else
	 	{
	    	cout << "   ";
	    }
    }
    
	cout << "|";
    cout << endl;
   }

   	cout << " -";
   	for (int j = 1; j <= BoardSize; j++)
   	{
    	cout << "---";
  	}
   	
	cout << "-";
   	cout << endl;
}

void board::DigitsInRow(int row)
{
	for(int i = 0; i < 9; i++)
	{
		rowDigits[i] = 0;
	}

	for(int j = 1; j<= numCols; j++)
	{
    	if(isBlank(row, j))
    	{
      		continue;
      	}
    	
		else
		{
    		rowDigits[j-1] = getCell(row,j);  //place each number from the row into arr
    	}
  	}
}

void board::DigitsInCol(int col)
{
	for(int i = 0; i < 9; i++)
	{
		colDigits[i] = 0;
	}

	for(int i = 1; i <= numRows; i++)
	{
		if(isBlank(i,col))
		{
      		continue;
      	}
    	else
    	{
    		colDigits[i-1] = getCell(i,col);  //place each number from the row into arr
    	}
  	}
}

void board::DigitsInSquare(int row, int col)
{
	int sq = squareNumber(row, col);
	int r, c = 0;

	switch(sq)  //reset cell to beginning of square
	{
    case 1:
      r = 1;
      c = 1;
      break;
    case 2:
      r = 1;
      c = 4;
      break;
    case 3:
      r = 1;
      c = 7;
      break;
    case 4:
      r = 4;
      c = 1;
      break;
    case 5:
      r = 4;
      c = 4;
      break;
    case 6:
      r = 4;
      c = 7;
      break;
    case 7:
      r = 7;
      c = 1;
      break;
    case 8:
      r = 7;
      c = 4;
      break;
    case 9:
      r = 7;
      c = 7;
      break;
    }

    for(int i = 0; i < 9; i++)
    {
      sqDigits[i] = 0;
    }

    for(int i = 1; i <= r + 2; i++) //stay in row of square
    {
    	for(int j = 1; j <= c+2; j++)   //stay in col of square
    	{
    		if(isBlank(i,col))
        	{
        		continue;
        	}
        	else
        	{
        		sqDigits[j] = getCell(i,col);  //place each number from the row into arr
        	}
      	}
    }
}

void board::printConflicts()
//look for Conflicts
//print them out
//move to next spot on board
{
  matrix <vector<bool> > conflicts(numRows, numCols);
  for(int i = 1; i <= numRows; i++)
  {
    for(int j = 1; j <= numCols; j++)
    {
      DigitsInRow(i);
      DigitsInCol(j);
      DigitsInSquare(i, j);
      for(int k = 1; k <= numDigits; k++)
      {
        int count = 0;
        for(int x = 0; x < 9; x++)
        {
          if(rowDigits[x] == k)
            count++;
          if(colDigits[x] == k)
            count++;
          if(sqDigits[x] == k)
            count++;

          if(count>1)
            conflicts[i][j][x] = true;
          else
            conflicts[i][j][x] = false;

          //cout<<conflicts[i][j][x];
        }
      }
    }
  }
}
