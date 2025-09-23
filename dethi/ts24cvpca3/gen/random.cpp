#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX_A = 1000000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 1000000);
    int q = gen.uniform(1, 1000000);
    cout << n << " " << q << endl;
    for (int i = 0; i < n; ++i) {
        cout << gen.uniform(-MAX_A, MAX_A) << " \n"[i == n - 1];
    }
    for (int i = 0; i < n; ++i) {
        cout << gen.uniform(-MAX_A, MAX_A) << " \n"[i == n - 1];
    }
    for (int i = 0; i < q; ++i) {
        cout << gen.uniform(1, 100) << ' ';
    }
    return 0;
}
