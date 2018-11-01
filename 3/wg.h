void grid::wordGenerator()
{
  numChars = numRows * numCols;
  int direction = 0;
  int count = 0;
  string word;
  int back_j, back_k;
  int x, y; //row, col

  ofstream fout;
  string filename = "words.txt"; //open file created in makeFile()
  fout.open(filename.c_str());

  if (!fout)
  {
    cout<<"ERROR: could not open file."<<endl;
  }

  else
  {
  	for(int j = 0; j < numRows-1; j++)
  	{
      direction = 0;
    	for(int k = 0; k < numCols; k++)
      {
  			//fout<<mat[j][k];
  			x = j;
  			y = k;
        count = 0;
        direction++;

        switch(direction)
        {
          case 1:
            x = j;
            while(count != numRows)
            {
              word += mat[x][y];
              fout<< word<< "\n";
              x++;
              count++;
              if(x == numRows)
                x = 0;
            }
            continue;
        }

      }
    }
  }
  fout.close();
}
