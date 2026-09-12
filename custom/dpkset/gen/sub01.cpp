#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 20);
    int k = gen.uniform(1, n);
    
    cout << n << " " << k << "\n";
    for (int i = 0; i < n; ++i) {
        cout << gen.uniform(-100, 100) << " ";
    }
    cout << "\n";
    for (int i = 1; i <= k; ++i) {
        cout << gen.uniform(-100, 100) << " ";
    }
    cout << "\n";

    return 0;
}
