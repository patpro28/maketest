#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX = 1 << 4;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 10;
    cout << t << endl;
    while (t--) {
        int n = gen.uniform(1, 10000);
        cout << n << '\n';
        for (int i = 0; i < n; ++i) {
            cout << (gen.uniform(1, MAX) << 20) << ' ';
        }
        cout << '\n';
    }
    return 0;
}
