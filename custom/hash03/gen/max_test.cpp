#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 100000;
    int m = gen.uniform<int>(n / 3, n / 2);
    int k = gen.uniform<int>(1, 10);
    string s(n, 'a');
    for (int i = 0; i < n; ++i) s[i] += k;
    int l = gen.uniform<int>(0, n - m);
    cout << s.substr(l, m) << "\n";
    cout << s << "\n";
    return 0;
}
