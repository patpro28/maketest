#include <cstdlib>
#include <iostream>
#include <string>
#include "random.h"
using namespace std;

int main(int, char** argv) {
    int seed = atoi(argv[1]);
    Random rng(seed);
    int t = seed < 5 ? rng.uniform(1, 100) : 100;
    cout << t << '\n';
    for (int tc = 0; tc < t; ++tc) {
        int alphabet = rng.uniform(2, 26);
        int offset = rng.uniform(0, 25);
        int copies[26];
        for (int& x : copies) x = rng.uniform(1, 2);
        int limit = seed < 5 ? rng.uniform(1, 30) : 500;
        string s;
        int prev = -1;
        while (true) {
            int c = rng.uniform(0, alphabet - 1);
            if (c == prev) continue;
            if ((int)s.size() + copies[c] > limit) break;
            s += string(copies[c], char('a' + (c + offset) % 26));
            prev = c;
        }
        if (s.empty()) s = string(copies[0], char('a' + offset));
        cout << s << '\n';
    }
}
