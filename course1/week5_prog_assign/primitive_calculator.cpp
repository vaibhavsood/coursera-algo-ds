#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using std::vector;

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  std::vector<int> optimal_values(n+1, 0);
  std::vector<int> optimal_moves(n+1, 0);

  for(int i = 2; i <= n; i++) {
    int min = INT_MAX;
    if (i % 3 == 0)
      if (optimal_values[i/3] < min) {
        min = optimal_values[i/3];
        optimal_moves[i] = 3;
      }
    if (i % 2 == 0)
      if (optimal_values[i/2] < min) {
        min = optimal_values[i/2];
        optimal_moves[i] = 2;
      }
    if (optimal_values[i-1] < min) {
        min = optimal_values[i-1];
        optimal_moves[i] = 1;
    }
    optimal_values[i] = min+1;
  }

  //std::cout << "optimal value: " << optimal_values[n] << std::endl;

  int push_index = n;

  while (push_index > 1) {
    //std::cout << "push index: " << push_index << std::endl;
    sequence.push_back(push_index);
    switch(optimal_moves[push_index]) {
      case 1:
           push_index = push_index - 1;
           break;
      case 2:
           push_index = push_index / 2;
           break;
      case 3:
           push_index = push_index / 3;
           break;
    } 
  }
  sequence.push_back(1);
  std::reverse(sequence.begin(), sequence.end());
  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
