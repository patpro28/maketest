#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n, q = n = 100;
    cout << n << " " << q << "\n";
    for (int i = 0; i < n; ++i) {
        cout << gen.uniform<int>(1, 100) << " ";
    }
    cout << "\n";
    while (q--) {
        int x = gen.uniform<int>(1, 100);
        bool small = gen.uniform_bool();
        if (small) {
            x = gen.uniform<int>(1, 10);
        }
        cout << x << "\n";
    }
    return 0;
}
