#include <iostream>

using namespace std;

enum class ECOLOR: unsigned int
{
  BLACK,
  WHITE,
  RED,
  BLUE
};

int main()
{
  ECOLOR color = ECOLOR::BLACK;

  /* 0 */
  cout << static_cast<int>(color) << endl;

  return 0;
}
