#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool find_cycle(vector<vector<int> > &adj, vector<bool> &visited, vector<int> &current_visit_list, int v) {
  visited[v] = true;
  current_visit_list.push_back(v);
  for (int i = 0; i < adj[v].size(); i++) {
    for (int j = 0; j < current_visit_list.size(); j++)
      if (current_visit_list[j] == adj[v][i])
        return true;
    if (visited[adj[v][i]] == false) {
      bool is_cyclic = find_cycle(adj, visited, current_visit_list, adj[v][i]);
      if (is_cyclic == true)
        return true;
    }
  }
  current_visit_list.pop_back();
  return false;
}

int acyclic(vector<vector<int> > &adj) {
  //write your code here
  vector<bool> visited(adj.size(), false);
  vector<int> current_visit_list;
  for (int i = 0; i < adj.size(); i++) {
    if (visited[i] == false)
      if (find_cycle(adj, visited, current_visit_list, i) == true)
        return 1; 
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
