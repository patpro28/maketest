#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, 1e5);
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        cout << gen.uniform<int>(1, 1e5) << " ";
    }
    return 0;
}
