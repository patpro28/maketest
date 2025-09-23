#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 10000);
    cout << t << endl;
    while (t--) {
        bool is_yes = gen.uniform_bool();
        int n = gen.uniform(1, 10000000), k;
        if (is_yes) {
            k = gen.uniform<int>(1, 2 * sqrt(n));
        } else {
            k = gen.uniform<int>(1, 10000000);
        }
        cout << n << " " << k << endl;
    }
    
    return 0;
}
