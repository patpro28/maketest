#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(4, 25);
    int l = gen.uniform(0, n - 1);
    
    cout << n << ' ' << l << '\n';
    for (int i = 0; i < n; ++i) {
        cout << gen.uniform(1, 20) << ' ';
    }
    cout << '\n';
    return 0;
}
