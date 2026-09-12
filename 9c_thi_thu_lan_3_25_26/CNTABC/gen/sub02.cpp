#include <iostream>
#include <vector>
#include <deque>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 2e5;
    string s = gen.lower_string(n, 'A', 'C');
    deque<pair<int, char>> queries;
    int q = gen.uniform(10000, 200000);
    cout << n << " " << q << '\n';
    while (q--) {
        int x = gen.uniform(1, n);
        char c = gen.uniform('A', 'Z');
        queries.emplace_front(x, s[x - 1]);
        s[x - 1] = c;
    }
    cout << s << '\n';
    for (auto& query : queries) {
        cout << query.first << " " << query.second << '\n';
    }
    return 0;
}
