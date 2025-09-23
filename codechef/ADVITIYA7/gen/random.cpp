#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 1000;
    cout << t << endl;
    while (t--) {
        int x = gen.uniform(1, 1000000000 / 4) * 4;
        cout << x << ' ' << 200 << '\n';
        cout << 2 << '\n';
        for (int i = 0; i < 199; ++i) {
            cout << gen.uniform(1, 100) << '\n';
        }
    }
    
    return 0;
}
