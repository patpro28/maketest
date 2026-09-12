#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, 1e5);
    int m = gen.uniform<int>(2, 10);
    int k = gen.uniform<int>(1, 10);
    string s(n, 'a');
    for (int i = 0; i < n; ++i) s[i] = gen.uniform<char>('a' + k, 'a' + k + gen.uniform(0, 1));
    int l = gen.uniform<int>(0, n - m);
    cout << s.substr(l, m) << "\n";
    cout << s << "\n";
    return 0;
}
