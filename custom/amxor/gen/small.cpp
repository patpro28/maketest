#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 10;
    cout << t << endl;
    for (int i = 0; i < t; ++i) {
        int n = gen.uniform(1, 10);
        cout << n << endl;
        for (int j = 0; j < n; ++j) {
            cout << gen.uniform(1, 100) << ' ';
        }
    }
    return 0;
}
