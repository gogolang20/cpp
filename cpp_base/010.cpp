#include <iostream>

using namespace std;

void add(int num)
{
  ++num;
}

void add_ref(int& num)
{
  ++num;
}

int main()
{
  // 指针

  // 引用

  
  int a = 1;
  cout << a << endl;

  add(a);
  cout << a << endl;

  //
  int b = 1;
  cout << b << endl;

  add_ref(b);
  cout << b << endl;

  return 0;
}
