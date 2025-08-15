#include <iostream>

using namespace std;

/*
* 多行注释
* 编译 运行
* g++ -o main 001.cpp
* ./main test
*/ 

int main(int argc, char* argv[])
{
  // 单行注释
  // 打印 hello world
  cout << "hello world" << endl;
  
  cout << argc << endl;
  cout << (*argv) << endl;
  cout << *(argv[1]) << endl;

  // system("pause"); // Windows System
  return 0;
}
