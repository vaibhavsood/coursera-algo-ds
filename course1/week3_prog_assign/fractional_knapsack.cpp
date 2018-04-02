#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct item {
  int value;
  int weight;
};

bool items_sort(item val1, item val2) {
  return ((double)val1.value / val1.weight) > ((double)val2.value / val2.weight);
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;

  // write your code here
  vector<item> items;

  for (int i = 0; i < weights.size(); i++) {
    item temp = { values[i], weights[i] };
    items.push_back(temp);
  }

  std::sort(items.begin(), items.end(), items_sort);

  for (int i = 0; i < items.size(); i++) {
    double value_added = (double)items[i].value;
    if (items[i].weight > capacity)
      value_added *= (double)capacity / items[i].weight;
    value += value_added;
    capacity -= items[i].weight; 
    if (capacity <= 0)
      break;
  }
 
  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
