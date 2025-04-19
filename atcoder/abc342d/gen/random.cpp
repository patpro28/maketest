#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int NMIN = 20000;
const int NMAX = 200000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(NMIN, NMAX);
    cout << n << '\n';
    vector<int> a(n);
    int zero = gen.uniform(0, 100);
    int one = gen.uniform(0, 100);
    for (int i = 0; i < n - zero - one; ++i)
        a[i] = gen.uniform(0, NMAX);
    for (int i = n - zero - one; i < n - zero; ++i)
        a[i] = 1;
    gen.shuffle(a.begin(), a.end());
    for (int i = 0; i < n; ++i)
        cout << a[i] << " \n"[i == n - 1];
    return 0;
}
