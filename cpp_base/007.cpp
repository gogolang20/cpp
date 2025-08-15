#include <iostream>

using namespace std;

// define function
int AddTwo(int, int);


int main()
{
  cout << AddTwo(1, 2) << endl;

  return 0;
}

// function logic
int AddTwo(int x, int y)
{
  return x + y;
}
