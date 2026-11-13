#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, dictionarySize;
    string s;
    cin >> n >> dictionarySize >> s;
    const long long inf = 1LL << 60;
    struct Node {
        array<int, 26> next;
        long long cost;
        Node() : next(), cost(1LL << 60) {}
    };
    vector<Node> trie(1);
    for (int i = 0; i < dictionarySize; ++i) {
        string word;
        long long cost;
        cin >> word >> cost;
        int node = 0;
        for (char ch : word) {
            int letter = ch - 'a';
            if (!trie[node].next[letter]) {
                trie[node].next[letter] = int(trie.size());
                trie.emplace_back();
            }
            node = trie[node].next[letter];
        }
        trie[node].cost = min(trie[node].cost, cost);
    }
    vector<long long> best(n + 1, inf);
    best[0] = 0;
    for (int i = 0; i < n; ++i) {
        if (best[i] == inf) continue;
        int node = 0;
        for (int j = i; j < n; ++j) {
            node = trie[node].next[s[j] - 'a'];
            if (!node) break;
            if (trie[node].cost != inf)
                best[j + 1] = min(best[j + 1], best[i] + trie[node].cost);
        }
    }
    cout << (best[n] == inf ? -1 : best[n]) << '\n';
}
