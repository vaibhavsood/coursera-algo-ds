#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_occurence_count(vector<int> &a, int left, int right, int num) {
  int count = 0;

  for (int i = left; i < right; i++) {
    if (a[i] == num)
      count++;
  } 

  return count;
}

int find_majority_element(vector<int> &a, int left, int right, int major1, int major2) {
  int size = (right - left)/2;
  int count;

  if (major1 == major2) return major1;

  if (major1 != -1) {
    count = get_occurence_count(a, left, right, major1);
    if (count > size)
      return major1;
  }

  if (major2 != -1) {
    count = get_occurence_count(a, left, right, major2);
    if (count > size)
      return major2;
  }

  return -1;
}

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  //write your code here
  int mid = left + (right - left)/2;
  int major1 = get_majority_element(a, left, mid);
  int major2 = get_majority_element(a, mid, right);
  //std::cout << "left, right: " << left << ", " << right << std::endl;
  //std::cout << "major1: " << major1 << std::endl;
  //std::cout << "major2: " << major2 << std::endl;
  return find_majority_element(a, left, right, major1, major2);
  //return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
