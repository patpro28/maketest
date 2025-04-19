#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int N = 2000;
const int MAX = 1000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(2, N);
    cout << n << '\n';
    for (int i = 0; i < n; ++i)
        cout << gen.uniform(1, MAX) << " \n"[i == n - 1];
    
    return 0;
}
