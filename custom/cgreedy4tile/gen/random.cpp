#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(2, 100);
    cout << n << "\n";
    for (int i = 0; i < n; ++i) {
        cout << gen.uniform(1, n) << " ";
    }
    cout << "\n";
    return 0;
}
