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
      matrix <vector <bool> > printConflicts();


      bool UsedInRow(int row, int num);
      bool UsedInCol(int col, int num);
      bool UsedInSquare(int row, int col, int num);
      ValueType firstEmptyCell();
      void solve(board b);
      void recursions();
      void shortestPath(int row, int col);
      void runShortest();

   private:
      matrix<ValueType> value;
      //matrix <vector<bool> > conflicts(int numRows, int numCols);
      int rowDigits[9];
      int colDigits[9];
      int sqDigits[9];
      int numRows;
      int numCols;
      int numDigits;
      int count;
      int row;
      int col;
      int max;
      int counter;

};

board::board(int sqSize)
   : value(BoardSize+1,BoardSize+1)
// Board constructor
{
   clear();
   numRows = sqSize;
   numCols = sqSize;
   numDigits = 9;
   count = 0;
   max = 0;
   counter = 0;
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
    for (int j = 1; j <= BoardSize; j++)
    {
      fin >> ch;
        // If the read char is not Blank
      if (ch != '.')
           setCell(i,j,ch-'0');   // Convert char to int
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
   return ostr;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in setCell");

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
         }
         cout << "-";
      	 cout << endl;
      }
      for (int j = 1; j <= BoardSize; j++)
      {
       if ((j-1) % SquareSize == 0)
          cout << "|";
       if (!isBlank(i,j))
          cout << " " << getCell(i,j) << " ";
       else
          cout << "   ";
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

  for(int j = 1; j<= 9; j++)  //traverse through columns
  {
    if(isBlank(row, j))
      rowDigits[j-1] = 0;
    else
      rowDigits[j-1] = getCell(row,j);  //place each number from the row into arr
    continue;
  }
}

void board::DigitsInCol(int col)
{
  for(int i = 0; i < 9; i++)
  {
    colDigits[i] = 0;
  }
  for(int i = 1; i <= 9; i++)   //traverse through rows
  {
    if(isBlank(i,col))
      continue;
    else
    colDigits[i-1] = getCell(i,col);  //place each number from the row into arr
  }
}

void board::DigitsInSquare(int row, int col)
{
  int sq = squareNumber(row, col);
  int r, c = 0;
  int count = 0;

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
    for(int x = 0; x < 9; x++)
    {
      sqDigits[x] = 0;
    }

    for(int i = r; i <= r + 2; i++) //stay in row of square
    {
      for(int j = c; j <= c+2; j++)   //stay in col of square
      {
        count++;          //ensure arry is in correct order
        if(isBlank(i,j))
          continue;
        else
          sqDigits[count-1] = getCell(i,j);  //place each number from the row into arr
      }
    }
}

bool board::UsedInRow(int row, int num)
{
  DigitsInRow(row);
  for(int i  = 0; i < 9; i++)
  {
    if(rowDigits[i] == num)
      return true;
    else
      continue;
  }
  return false;
}

bool board::UsedInCol(int col, int num)
{
  DigitsInCol(col);
  for(int i  = 0; i < 9; i++)
  {
    if(colDigits[i] == num)
      return true;
    else
      continue;
  }
  return false;
}

bool board::UsedInSquare(int row, int col, int num)
{
  DigitsInSquare(row, col);
  for(int i  = 0; i < 9; i++)
  {
    if(sqDigits[i] == num)
      return true;
  }
  return false;
}


matrix <vector <bool> > board::printConflicts()
{
  //vector <bool> temp;
  matrix <vector<bool> > conflicts(9, 9);
  bool r, c, s;
  for(int i = 1; i <= 9; i++)//rows
  {
    for(int j = 1; j <= 9; j++)//cols
    {
      for(int k = 1; k <= 9; k++)//digits
      {
        conflicts[i][j].resize(9);
        r = UsedInRow(i, k);
        c = UsedInCol(j, k);
        s = UsedInSquare(i, j, k);

        if(r || c || s)
          conflicts[i][j].push_back(true);
        else
          conflicts[i][j].push_back(false);
      }
    }
  }
  return conflicts;
}

ValueType board::firstEmptyCell()
{
  for(int i = 1; i <= 9; i++) //rows
  {
    for(int j = 1; j <= 9; j++) //cols
    {
      if (isBlank(i, j) || getCell(i, j) == 'Z')
      {
        row = i;
        col = j;
        return getCell(i, j);
      }
      else
        continue;
    }
  }
}


void board::solve(board b)
{
  count ++;
  if(firstEmptyCell() == 'Z') //if fully solved
  {
    cout<<"Board is solved!\n";
    b.print();
    exit(EXIT_FAILURE); //"return -1"
  }
  else
  {
    runShortest();
    //firstEmptyCell(); //sets row and col
    //cout<<"row: "<<row;
    //cout<<"col:"<<col;

    for(int k = 1; k <= 9; k++)//digits
    {
      bool r = UsedInRow(row, k); //digit is used in the row
      bool c = UsedInCol(col, k);
      bool s = UsedInSquare(row, col, k);
      bool illegal = (r || c || s); //no legal choice for digit

      if(illegal == true && k == 9) //deadend
        break;

      else if(illegal == true)  //if choice is illegal
        continue;

      else
      {
        b.setCell(row, col, k);
        b.print();
        b.solve(b); //recursive call not working
        b.setCell(row, col, 0);
        continue;
      }
    }
  }
}


void board::recursions()
{
  cout<<"\n\n\nTotal # of recursions: "<< count;
}


void board::shortestPath(int row, int col)
{
  count++;
  int used[] = {0,0,0,0,0,0,0,0,0};
  counter = 0;


  if(getCell(row, col) == 'Z')
    exit(EXIT_FAILURE);

  for(int k = 1; k <= 9; k++)
  {
    if(UsedInRow(row, k) || UsedInCol(col, k) || UsedInSquare(row, col, k))
      used[k-1] = k;
  }

  for(int x = 0; x < 9; x++)
  {
    if(used[x] != 0)
      counter ++;
    //cout<<used[x];
  }
}

void board::runShortest()
{
  vector <int> shortest(2,0);
  for(int i = 1; i <=9; i++)
  {
    for(int j = 1; j <=9; j++)
    {
      if(!isBlank(i, j))  //if already filled
        continue;

      //cout<<"\nCounter: "<<counter;
      //cout<<"\nMax: "<<max;
      if(counter > max)
      {
        max = counter;
        shortest.push_back(i);
        shortest.push_back(j);
        row = i;
        col = j;
      }
      //cout<<"\nRow: "<<i;
      //cout<<"\nCol: "<<j;
      //cout<<"\nCount: "<<count<<"\n\n";
      shortestPath(i, j);
    }
  }
}
