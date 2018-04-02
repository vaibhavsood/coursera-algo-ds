#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool explore(vector<vector<int> > &adj, vector<bool> &visited, int x, int y) {
  visited[x] = true;
  if (x == y)
    return true;
  for (int i = 0; i < adj[x].size(); i++) {
    if (adj[x][i] == x || visited[adj[x][i]] == true)
      continue;
    bool found = explore(adj, visited, adj[x][i], y);
    if (found == true)
      return true;
  } 
  return false;
}

int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  vector<bool> visited(adj.size(), false);
  if (explore(adj, visited, x, y) == true)
    return 1;
  else
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
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
