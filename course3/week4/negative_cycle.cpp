#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  //write your code here
  vector<int> dists(adj.size(), 100000001);
  dists[0] = 0;
  int node_count = 0;
  while (node_count != adj.size()-1) {
    for (int i = 0; i < adj.size(); i++) {
      for (int j = 0; j < adj[i].size(); j++) {
        if (dists[adj[i][j]] > (dists[i]+cost[i][j]))
          dists[adj[i][j]] = dists[i]+cost[i][j];
      }
    }
    node_count++;
  }
  for (int i = 0; i < adj.size(); i++) {
    for (int j = 0; j < adj[i].size(); j++) {
      if (dists[adj[i][j]] > (dists[i]+cost[i][j]))
        return 1;
    }
  }
  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
