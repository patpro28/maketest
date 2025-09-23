#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX = 1 << 4;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 1;
    cout << t << endl;
    while (t--) {
        int n = 100000;
        cout << n << '\n';
        for (int i = 0; i < n; ++i) {
            cout << (gen.uniform(1, MAX) << 25) << ' ';
        }
        cout << '\n';
    }
    return 0;
}
