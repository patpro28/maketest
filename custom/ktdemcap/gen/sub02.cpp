#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(2, 2e5);
    int k = gen.uniform<int>(1, 1e8);
    cout << n << " " << k << endl;
    vector<long long> a(n);
    for (int i = 0; i * 2 < n; ++i)
        a[i] = gen.uniform<long long>(1, 1e9);
    for (int i = n / 2; i < n; ++i)
        a[i] = a[i - n / 2] + gen.uniform<int>(-1, 1) * k;
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
