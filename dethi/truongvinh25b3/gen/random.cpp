#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 22);
    vector<char> t;
    for (int i = 0; i < n; ++i) {
        char c = gen.uniform('a', 'z');
        while (count(t.begin(), t.end(), c)) {
            c = gen.uniform('a', 'z');
        }
        t.push_back(c);
    }
    int m = gen.uniform(1, 100000);
    string s;
    for (int i = 0; i < m; ++i) {
        s.push_back(t[gen.uniform(0, n - 1)]);
    }
    cout << s << "\n";
    vector<int> a = {1, 2, 3, 4};
    gen.shuffle(a.begin(), a.end());
    for (auto x : a) cout << x << ' ';
    cout << "\n";
    return 0;
}
