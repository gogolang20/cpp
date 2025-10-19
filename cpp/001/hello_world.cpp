#include <iostream>

using namespace std;

/**
 * 
 * 多行注释
 * 
 * 编译
 * g++ -o main hello_world.cpp
 * 
 * 运行
 * ./main 001 002 003
 */

// 单行注释
// main() 程序的入口
// int argc, const char* argv[] 需要外部参数的时候添加
int main(int argc, const char* argv[])
{
    // 打印 hello world
    cout << "hello world" << endl;

    // 打印外部参数信息
    cout << "number of args: " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << endl;
    }

    // system("pause"); // Windows System
    return 0; 
}
