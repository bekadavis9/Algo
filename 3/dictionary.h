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
//#include "heap.hpp"
using namespace std;

class dictionary
{
  public:
    dictionary();
    friend ostream& operator<< (ostream &ostr, const vector<string>& words);
    void selectionSort();
    int binarySearch(string target);
    void quickSort(vector <string> &words, int left, int right);
    void heapSort();


  private:
    vector <string> words;
    vector <string> sorted;
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
    length++;
    words.push_back(word);
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

  ofstream fout;
  string filename = "dictionary-sorted.txt"; //create output file
  fout.open(filename.c_str());

  if(!fout)
  {
    cout<<"ERROR: could not open file."<<endl;
  }

  else
  {
    for( int i = 0; i < words.size()-1; ++i)
    {
      minIndex = i;
      tmp = words[i];
      for (int j = i + 1; j < words.size(); ++j)
      {
        if (words[j] <= words[minIndex])
          minIndex = j;
      }

      if(minIndex != i)
      {
        tmp = words[minIndex];
        words[minIndex] = words[i];
        words[i] = tmp;
      }


      fout<< words[i] << "\n";
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
      cout<< "\nFound: "<< target;
      return i;
    }
    else
    {
      i++;
      continue;
    }
  }

  int left = 0;
  int right = (int)words.size()-1;
  int mid = (left + right)/2;
  return -1;
}

void dictionary::quickSort(&words, int left, int right)
{
  int j, k;
  string tmp;
  left = words.front();
  right = words.back();
  int midpoint = left + (right-left) /2;
  string pivot = words[midpoint]

  while(j<right || k>right)
  {
    while(words[j] < pivot)
    {
      j++
    }
    while(words[k] > pivot)
    {
      k--;
    }
    if(j <= k)
    {
      tmp = words[j];
      words[j] = words[k];
      words[k] = tmp;

      j++;
      k--;
    }
    else
    {
      if(j < right)
        quickSort(words, j, right);
      if(k > left)
        quickSort(words, left, k);
    }
  }
}



/*
void dictionary::heapSort()
{
  buildMaxHeap(words);
  maxHeapify(words);
}
*/
