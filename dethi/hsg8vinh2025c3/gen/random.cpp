#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 100000;
    int p = 10000000;
    cout << n << " " << p << endl;
    for (int i = 0; i < n; i++) {
        cout << gen.uniform<int>(1, 1000000) << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << gen.uniform<int>(1, 10000) << " ";
    }
    return 0;
}
