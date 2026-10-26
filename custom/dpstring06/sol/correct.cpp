#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const long long INF = 1LL << 60, NEG = -INF;
    (void) INF; (void) NEG;
    int n; string s;
    cin >> n >> s;
    vector<long long> w(n); for (auto &v : w) cin >> v;
    // States: ends in one vowel, one consonant, two consonants.
    long long vowel = NEG, consonant = NEG, two = NEG;
    for (int i = 0; i < n; ++i) {
        if (string("aeiou").find(s[i]) != string::npos)
            vowel = max(vowel, max(0LL, max(consonant, two)) + w[i]);
        else {
            long long old = consonant;
            consonant = max(consonant, max(0LL, vowel) + w[i]);
            if (old != NEG) two = max(two, old + w[i]);
        }
    }
    cout << max(0LL, max(vowel, max(consonant, two))) << '\n';
}
