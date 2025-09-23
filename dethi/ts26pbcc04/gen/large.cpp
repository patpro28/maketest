#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 100000;
    int k = gen.uniform<int>(50, 100);
    cout << n << ' ' << k << '\n';
    vector<int> val;
    for (int i = 0; i < k; ++i)
        val.push_back(gen.uniform<int>(1, 1e9));
    sort(val.begin(), val.end());
    vector<int> a(n);
    for (int i = 0; i + 1 < n; ++i)
        a[i] = val[gen.uniform<int>(0, k - 2)];
    a[n - 1] = val[k - 1];
    gen.shuffle(a.begin(), a.end());
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    cout << '\n';
    for (int i = 0; i < k; ++i)
        cout << gen.uniform<int>(1, 100) << ' ';
    cout << '\n';
    return 0;
}
