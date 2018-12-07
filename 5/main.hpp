/*
Algorithms 12/5/18
Project #5 main.hpp file
Word Search
Rebekah Davis and Julian Perez
Group ID: DAVPER (24)
*/

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
      bool isLegal(int i, int j); // Return value stored at (i,j) in maze

      void setVertices();
      void setEdges();

      void setMap(int i, int j, int n);
      int getMap(int i, int j) const;

      void mapMazeToGraph(graph &g);

      void findPathRecursive(int sR, int sC, int dR, int dC);


   private:
      int rows; // number of rows in the maze
      int cols; // number of columns in the maze

      matrix<bool> value;   //true if O, false if X
      matrix<int> map;      // Mapping from maze (i,j) values to node index values
                            //the maze in matrix form
      graph g;
      vector <string> path;
      matrix<node> v;

      //bool isNode;

};

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


void maze::setVertices()
{
  v.resize(rows, cols);
  NodeWeight w0 = 0;
  NodeWeight w1 = 1;
  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      if(value[i][j] == true)
      {
        node n;
        v[i][j] = n;
        v[i][j].setId(w1);
      }
      else
      {
        node n;
        v[i][j] = n;
        v[i][j].setId(w0);
      }
    }
  }
}




//don't necessarily need
void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n.
{

}

/*
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

  if(isLegal(i,j)) //if 0
    g.addNode(0);
  else
    exit(EXIT_FAILURE); //"return -1"

  switch(y)
  {
    case 1: //up
    y = j-1;
    if(isLegal(x,y))
      g.addNode(0);
    else
      break;

    case 2: //down
    y = j+1;
    if(isLegal(x,y))
      g.addNode(0);
    else
      break;

    switch(x)
    {
      case 3: //left
          x = i-1;
          if(isLegal(x,y))
            g.addNode(0);
          else
            break;

      case 4: //right
          x = i+1;
          if(isLegal(x,y))
            g.addNode(0);
          else
            break;
    }
  }
}
*/

/*int maze ::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
}
*/




void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
  NodeWeight w = 0;
  int x, y;
  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      if(value[i][j] == true)
      {
        g.addNode(w);
        g.mark(i,j);
      }
      else
        continue;
    }
  }

  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      switch(y)
      {
        case 1: //up
        y = j-1;
        x = i;
        if(value[x][y] == true && value[i][j] == true)
        {
          g.addEdge(i,j,w);
        }
        else
          break;

        case 2: //down
        y = j+1;
        x = i;
        if(value[x][y] == true && value[i][j] == true)
        {
          g.addEdge(i,j,w);
        }
        else
          break;

        switch(x)
        {
          case 3: //left
              x = i-1;
              y = j;
              if(value[x][y] == true && value[i][j] == true)
              {
                g.addEdge(i,j,w);
              }
              else
                break;

          case 4: //right
              x = i+1;
              y = j;
              if(value[x][y] == true && value[i][j] == true)
              {
                g.addEdge(i,j,w);
              }
              else
                break;
        }
      }
    }
  }
}

void maze::findPathRecursive(
    int sourceR, int sourceC, int destR, int destC)
{
  int x, y;
  g.clearVisit();

  if(value[sourceR][sourceC] == false || value[destR][destC] == false)
    exit(EXIT_FAILURE);

  //v[sourceR][sourceC].visit();

  for(int i = sourceR; i < rows; i++)
  {
    for(int j = sourceC; j < cols; j++)
    {
      switch(y)
      {
        case 1: //up
        y = j-1;
        x = i;
        if(v[x][y].getId() == 1)
        {
          path.push_back("up  ");
          findPathRecursive(x, y, destR, destC);
        }
        else
          break;
/*
        case 2: //down
        y = j+1;
        x = i;
        if(v[x][y].getId() == 1)
        {
          path.push_back("down  ");
          findPathRecursive(x, y, destR, destC);
        }
        else
          break;

        switch(x)
        {
          case 3: //left
              x = i-1;
              y = j;
              if(v[x][y].getId() == 1)
              {
                path.push_back("left  ");
                findPathRecursive(x, y, destR, destC);
              }
              else
                break;

          case 4: //right
              x = i+1;
              y = j;
              if(v[x][y].getId() == 1)
              {
                path.push_back("right  ");
                findPathRecursive(x, y, destR, destC);
              }
              else
                break;
        }*/
      }
    }
  }
  for(int a = 0; a < path.size(); a++)
  {
    cout<< path[a];
  }
}
