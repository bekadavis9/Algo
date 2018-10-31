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
#include "grid.h"
using namespace std;

class dictionary
{
  public:
    dictionary();
    friend ostream& operator<< (ostream &ostr, const vector<string>& words);
    void selectionSort();
    int binarySearch(string target);

  private:
    vector <string> words;
    grid g;
    int length;
};

dictionary::dictionary()
{
  string word;
  int length = 0;
  ifstream f_in;
	string filename = "dictionary.txt";
	f_in.open(filename.c_str());

  if (!f_in)
		cout<<"ERROR: could not open file."<<endl;

  while(!f_in.eof())
	{
    f_in>> word;
    words.push_back(word);
    length++;
  }
  f_in.close();
}

ostream& operator<< (ostream &ostr, const vector<string>& words)
{
  for(int i = 0; i<words.size(); i++)
  {
    cout<< words[i];
    cout<< "\n";
  }
  return ostr;
}

void dictionary::selectionSort()
{
  int minIndex;
  string tmp;
  //int length = numRows * numCols;

  ofstream fout;
  string filename = "dictionary-sorted.txt"; //create output file
  fout.open(filename.c_str());

  if(!fout)
  {
    cout<<"ERROR: could not open file."<<endl;
  }

  else
  {
    for( int i = 0; i < length - 1; i++)
    {
      minIndex = i;
      tmp = words[i];
      for (int j = i + 1; j < length; j++)
      {
        if (words[j] < tmp)
          tmp = words[j];
          minIndex = j;
      }
      words[minIndex] = words[i];
      words[i] = tmp;
    }
  }
  fout.close();
}



int dictionary::binarySearch(string target)
{
  int i = 0;
  while(i < words.size())
  {
    if(words[i] == target)
    {
      cout<< "Found: "<< target;
      return i;
    }
    else
    {
      i++;
      continue;
    }
  }
  return -1;
}
