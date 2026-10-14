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
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        a[i] = gen.uniform<int>(1, 1e6);
    }
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++) {
        cout << a[i] << (i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
