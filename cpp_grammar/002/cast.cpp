#include <iostream>

using namespace std;

int main()
{
  // static_cast
  double b = 3.14f;
  cout << b << endl;

  int i = static_cast<int>(b);
  cout << i << endl;


  // dynamic_cast

  // const_cast

  // reinterpret_cast

  return 0;
}
