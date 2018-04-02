#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  vector<int> dists(adj.size(), -1);
  queue<int> untouched;
  dists[s] = 0;
  untouched.push(s);
  while (untouched.empty() == false) {
    int next = untouched.front();
    untouched.pop();
    for (int i = 0; i < adj[next].size(); i++) {
      if (dists[adj[next][i]] == -1) {
        dists[adj[next][i]] = dists[next]+1;
        if (adj[next][i] == t)
          return dists[adj[next][i]];
        untouched.push(adj[next][i]);
      }
    } 
  }
  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
