/*
Author: Tu Pham Anh
Date: 2025/02/14 - 18:28
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

struct Trie {
  struct Node {
    int cnt = 0; // Number of integers that end in subtree of this node
    int next[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  };

  vector<Node> nodes;

  Trie() {
    nodes.emplace_back();
  }

  void insert(string x) {
    int p = 0;
    for (char c : x) {
      int d = c - '0';
      if (nodes[p].next[d] == -1) {
        nodes[p].next[d] = nodes.size();
        nodes.emplace_back();
      }
      p = nodes[p].next[d];
      nodes[p].cnt++;
    }
  }

  long long cal(string x, vector<int> &orders) {
    long long res = 0;
    int p = 0;
    for (char c : x) {
      int d = c - '0';
      for (auto o : orders) {
        if (o == d) break;
        if (nodes[p].next[o] != -1) {
          res += nodes[nodes[p].next[o]].cnt;
        }
      }
      if (nodes[p].next[d] == -1) break;
      p = nodes[p].next[d];
    }
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);
  
  int n;
  cin >> n;
  Trie trie;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    while (s.size() < 19) s = "0" + s;
    trie.insert(s);
  }

  int q;
  cin >> q;
  while (q--) {
    string s;
    vector<int> orders(10);
    for (int i = 0; i < 10; ++i) {
      cin >> orders[i];
    }
    cin >> s;
    while (s.size() < 19) s = "0" + s;
    cout << trie.cal(s, orders) << '\n';
  }

  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
  return 0;
}