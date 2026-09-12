#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    char c[] = {'W', 'D', 'L'};

    int n = 10;
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int len = gen.uniform(1, 100);
        int l = gen.uniform(0, 2);
        int r = gen.uniform(l, 2);
        for (int j = 0; j < len; ++j)
            cout << c[gen.uniform(l, r)];
        cout << '\n';
    }
    return 0;
}
