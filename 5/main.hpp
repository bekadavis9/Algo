// Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"

using namespace std;

class maze
{
   public:
      maze(ifstream &fin);
      void print(int,int,int,int);
      bool isLegal(int i, int j);

      void setMap(int i, int j, int n);
      int getMap(int i, int j) const;
      void mapMazeToGraph(graph &g);
      vector <node> setNodes();
      vector <int> findPathRecursive(int i, int j);


   private:
      int rows; // number of rows in the maze
      int cols; // number of columns in the maze

      matrix<bool> value;   //true if O, false if X
      matrix<int> map;      // Mapping from maze (i,j) values to node index values
                            //the maze in matrix form
      graph g;
      vector <node> v;

};

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n.
{
  //up, down, left, right - check if O
      //if yes, add to map
      //if no, check next location

  //i = row(x), j = col(y)

  int x, y;
  x = i;
  y = j;

  //check if x,y are 0 or beyond end (i,j = 0 or length())

  if(value[i][j]) //if 0
    g.addNode(0);
  else
    exit(EXIT_FAILURE); //"return -1"

  switch(y)
  {
    case 1: //up
    y = j-1;
    if(value[x][y])
      g.addNode(0);
    else
      break;

    case 2: //down
    y = j+1;
    if(value[x][y])
      g.addNode(0);
    else
      break;

    switch(x)
    {
      case 3: //left
          x = i-1;
          if(value[x][y])
            g.addNode(0);
          else
            break;

      case 4: //right
          x = i+1;
          if(value[x][y])
            g.addNode(0);
          else
            break;
    }
  }
}

int maze ::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;

   char x;

   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
	 fin >> x;
	 if (x == 'O')
            value[i][j] = true;
	 else
	    value[i][j] = false;
      }

   map.resize(rows,cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{

}

vector <node> maze::setNodes()
{
  node n;
  int count = 1; //IDs are 1-81
  for(int j= 0; j < cols; j++)
  {
    for(int i = 0; i < rows; i++)
    {
      n.setNode(count, 0, false, false);
      v.push_back(n);
      count ++;
    }
  }
  return v;
}


vector <int> maze::findPathRecursive(int i, int j)
{
  for(int a = 0; a < v.size(); a++)
  {
    v[a].unVisit();
  }

  int id = map[i][j].getID();

  v(id).visit();
  int x = i;
  int y = j;

  switch(y)
  {
    case 1: //up
    y = j-1;
    if(map[x][y].isVisited())
      break;
    else
      findPathRecursive(x,y);

    case 2: //down
    y = j+1;
    if(map[x][y].isVisited())
      break;
    else
      findPathRecursive(x,y);

    switch(x)
    {
      case 3: //left
          x = i-1;
          if(map[x][y].isVisited())
            break;
          else
            findPathRecursive(x,y);

      case 4: //right
          x = i+1;
          if(map[x][y].isVisited())
            break;
          else
            findPathRecursive(x,y);
    }
  }

}
