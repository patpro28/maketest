#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAXN = 16;
const int MAXT = 100;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = gen.uniform(1, MAXN);
    int T = gen.uniform(1, MAXT);
    
    cout << N << '\n';
    cout << T << '\n';
    for (int i = 0; i < N; ++i)
        cout << gen.uniform(1, 100000) << ' ';
    cout << '\n';
    for (auto x: gen.gen_sum<int>(max(T * 2, N), N, 1, 10000))
        cout << x << ' ';
    cout << '\n';
    return 0;
}
