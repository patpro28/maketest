// Independent bit-parallel LCS; each bit represents a position in A.
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    int n, m; string a, b;
    cin >> n >> m >> a >> b;
    int words = (n + 63) / 64;
    vector<vector<uint64_t> > masks(26, vector<uint64_t>(words, 0));
    for (int i = 0; i < n; ++i) masks[a[i] - 'a'][i / 64] |= uint64_t(1) << (i % 64);
    vector<uint64_t> state(words, 0);
    for (char c : b) {
        uint64_t carry = 1, borrow = 0;
        for (int j = 0; j < words; ++j) {
            uint64_t old = state[j];
            uint64_t x = old | masks[c - 'a'][j];
            uint64_t y = (old << 1) | carry;
            carry = old >> 63;
            uint64_t difference = x - y;
            uint64_t next_borrow = (x < y) || (difference < borrow);
            difference -= borrow;
            borrow = next_borrow;
            state[j] = x & ~difference;
        }
    }
    int answer = 0;
    for (uint64_t word : state) answer += __builtin_popcountll(word);
    cout << answer << '\n';
}
