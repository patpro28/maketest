#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 100000;
    int k = 100;
    cout << n << ' ' << k << '\n';
    for (int i = 0; i < n; ++i)
        cout << gen.uniform<int>(1, 1e9) << ' ';
    cout << '\n';
    for (int i = 0; i < k; ++i)
        cout << gen.uniform<int>(1, 1e6) << ' ';
    cout << '\n';
    return 0;
}
