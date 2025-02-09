  using namespace std;
  
  #include <iostream>
  #include <vector>
  #include <math.h>
  #include <cstdlib>
  
  // Function to build the grid
  vector<vector<int>> buildGrid(int rows, int cols)
  {
      int r= 0;
      vector<vector<int>> v(rows, vector<int> (cols, 0)) ;
      srand(time(0));
      for (int i=0; i<rows; i++)
      {
        for (int j=0; j<cols; j++)
        {
          r= rand()%9+1;
  //        cout <<"i:"<<i<<endl;
  //        cout <<"j:"<<j<<endl;
  //        cout <<"r:"<<r<<endl;
          v[i][j]=r;
        }
      }
      return v;
  }
  
  // Function to print the grid
  void printGrid(vector<vector<int>> grid) 
  {
      for (vector<int> row : grid) 
      {
          for (int val : row) 
          {
              cout << val << " ";
          }
          cout << endl;
      }
  }
  
  
  
  int main() 
  {
      int i = 1;
      
      while (i < 2)
    {
      int rows = (int)(pow(2,i));
      int cols = (int)(pow(2,i));
  
      vector<vector<int>> grid = buildGrid(rows, cols);
      cout << "Grid:" << rows <<"x" <<cols << endl;
      printGrid(grid);
      i++;
    }
  
      return 0;
  }
  
