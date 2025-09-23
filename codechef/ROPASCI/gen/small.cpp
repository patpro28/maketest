#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 1000);
    auto N = gen.gen_sum(5000, t);

    const char c[] = {'R', 'P', 'S'};

    cout << t << '\n';
    for (int i = 0; i < t; ++i) {
        cout << N[i] << '\n';
        string s(N[i], ' ');
        for (int j = 0; j < N[i]; ++j) {
            s[j] = c[gen.uniform(0, 2)];
        }
        cout << s << '\n';
    }
    return 0;
}
