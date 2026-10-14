#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, 1e6);
    cout << n << '\n';
    for(int i = 0; i < n / 2; i++) {
        int x = gen.uniform<int>(1, 1e6);
        cout << x << ' ';
    }
    cout << 1000000 << ' ';
    for (int i = n / 2 + 1; i < n; i++) {
        int x = gen.uniform<int>(9e5, 1e6);
        cout << x << (i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
