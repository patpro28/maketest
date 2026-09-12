#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, 1000);
    cout << n << "\n";
    auto a = gen.perm<int>(n);
    for (int i = 0; i < n; i++) {
        cout << a[i] + 1 << ' ';
    }
    cout << "\n";
    a = gen.perm<int>(n);
    for (int i = 0; i < n; i++) {
        cout << a[i] + 1 << ' ';
    }
    cout << "\n";
    return 0;
}
