#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

class node_dist {
public:
  int node;
  int dist;
};

class compare_dists {
public:
  bool operator() (node_dist node1, node_dist node2) {
    return node1.dist > node2.dist;
  }
};

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
  vector<int> dists(adj.size(), 100000001);
  vector<int> seen_nodes;
  priority_queue<node_dist, std::vector<node_dist>, compare_dists> pq;
  dists[s] = 0;
  for (int i = 0; i < adj.size(); i++) {
    node_dist pq_elem;
    pq_elem.node = i;
    if (i == s)
      pq_elem.dist = 0;
    else
      pq_elem.dist = 100000001;
    pq.push(pq_elem);
  }
  while (pq.empty() == false) {
    node_dist min_node = pq.top();
    pq.pop();
    for (int i = 0; i < seen_nodes.size(); i++)
      if (min_node.node == seen_nodes[i])
        continue;
    if (min_node.node == t) {
      if (dists[min_node.node] == 100000001)
        dists[min_node.node] = -1;
      return dists[min_node.node];
    }
    for (int i = 0; i < adj[min_node.node].size(); i++) {
      if (dists[adj[min_node.node][i]] > (dists[min_node.node]+cost[min_node.node][i])) {
        dists[adj[min_node.node][i]] = dists[min_node.node]+cost[min_node.node][i];
        node_dist up_pq_elem;
        up_pq_elem.node = adj[min_node.node][i];
        up_pq_elem.dist = dists[adj[min_node.node][i]];
        pq.push(up_pq_elem);
      }
    }
    seen_nodes.push_back(min_node.node);
  }
  return -1;
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
