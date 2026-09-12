#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 100000);
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        string ten = gen.lower_string(gen.uniform(1, 5));
        int toan = gen.uniform(0, 10);
        int tin = gen.uniform(0, 10);
        cout << ten << ' ' << toan << ' ' << tin << '\n';
    }

    return 0;
}
