#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAXN = 1e9;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 3000;
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        int n = gen.uniform(2, MAXN);
        cout << n << "\n";
    }
    return 0;
}
