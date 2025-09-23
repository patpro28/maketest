#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAXN = 2e5;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, MAXN);
    int k = gen.uniform(1, n);
    cout << n << " " << k << "\n";
    for (int i = 1; i <= n; i++) {
        int p = gen.uniform(1, 12);
        cout << gen.uniform<long long>(1, pow(10, p)) << " ";
    }
    cout << "\n";
    return 0;
}
