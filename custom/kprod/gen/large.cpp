#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

void gen_test(int n, Random &gen) {
    int k = gen.uniform<int>(1, n);
    int m = gen.uniform<int>(1, 1000000000);
    cout << n << " " << k << " " << m << endl;
    for (int i = 0; i < n; ++i) {
        cout << gen.uniform<int>(0, 1000000000) << " \n"[i == n - 1];
    }
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 3;
    cout << t << endl;
    gen_test(299998, gen);
    gen_test(1, gen);
    gen_test(1, gen);
    
    return 0;
}
