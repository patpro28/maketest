#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 1;
    cout << t << '\n';
    for (int i = 0; i < t; ++i) {
      int n = gen.uniform(1, 20);
      cout << n << '\n';
    }
    return 0;
}
