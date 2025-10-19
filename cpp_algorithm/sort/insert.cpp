#include <vector>

void insert_sort(std::vector<int> arr)
{
  for (int i = 1; i < arr.size(); i++) {
    for (int j = i; j > 0 && arr[j-1] > arr[j]; j--) {
      int temp = arr[j-1];
      arr[j-1] = arr[j];
      arr[j] = temp;
    }
  }
}
