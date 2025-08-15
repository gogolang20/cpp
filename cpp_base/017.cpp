#include <iostream>

using namespace std;

template <typename T>
T AddTwo(T x, T y)
{
  return x + y;
}

int main()
{
  cout << AddTwo(3, 5) << endl;

  cout << AddTwo(3.14, 5.16) << endl;

  return 0;
}
