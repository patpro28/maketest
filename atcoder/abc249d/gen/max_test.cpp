#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 2e5;
    cout << n << "\n";
    vector<int> a(n);
    fill(a.begin(), a.begin() + n / 2, 1);
    for (int i = n / 2; i < n - 1; i++) {
        a[i] = gen.uniform<int>(1, 2e5);
    }
    a[n - 1] = 2e5;
    gen.shuffle(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        cout << a[i] << (i == n - 1 ? "\n" : " ");
    }
    return 0;
}
