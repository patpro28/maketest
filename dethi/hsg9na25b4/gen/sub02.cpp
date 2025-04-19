#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int NMAX = 20;
int AMAX = 2;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, NMAX);
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        cout << gen.uniform(1, n) << " \n"[i == n - 1];
    }


    return 0;
}
