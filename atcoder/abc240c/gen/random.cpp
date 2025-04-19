#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 100);
    int x = gen.uniform(1, 10000);
    cout << n << " " << x << endl;
    for(int i = 0; i < n; i++) {
        auto p = gen.uniform_pair(1, 100);
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}
