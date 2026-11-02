#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int k; cin >> k;
    vector<string> strings(k);
    for (string &s : strings) cin >> s;
    int shortest = 0;
    for (int i = 1; i < k; ++i)
        if (strings[i].size() < strings[shortest].size()) shortest = i;
    swap(strings[0], strings[shortest]);
    const string &base = strings[0];
    int length = base.size(), states = 1 << length;
    vector<unsigned char> bits(states, 0), highest(states, 0), valid(states, 1);
    for (int mask = 1; mask < states; ++mask) {
        highest[mask] = mask == 1 ? 0 : highest[mask >> 1] + 1;
        bits[mask] = bits[mask >> 1] + (mask & 1);
    }
    vector<int> pos(states);
    for (int index = 1; index < k; ++index) {
        const string &s = strings[index];
        int n = s.size();
        vector<array<int, 26> > next(n + 1);
        next[n].fill(n + 1);
        for (int p = n - 1; p >= 0; --p) {
            next[p] = next[p + 1];
            next[p][s[p] - 'a'] = p + 1;
        }
        pos[0] = 0;
        for (int mask = 1; mask < states; ++mask) {
            if (!valid[mask]) { pos[mask] = n + 1; continue; }
            int h = highest[mask], parent = mask ^ (1 << h);
            int end = pos[parent];
            pos[mask] = end <= n ? next[end][base[h] - 'a'] : n + 1;
            if (pos[mask] > n) valid[mask] = 0;
        }
    }
    int answer = 0;
    for (int mask = 0; mask < states; ++mask)
        if (valid[mask]) answer = max(answer, int(bits[mask]));
    cout << answer << '\n';
}
