#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 20);
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        cout << gen.uniform(1, 100) << ' ';
    }
    return 0;
}
