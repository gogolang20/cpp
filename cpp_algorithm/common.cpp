#include <vector>

/* 交换数组两个元素的位置 */
void swap(std::vector<int> arr, int i, int j)
{
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}
