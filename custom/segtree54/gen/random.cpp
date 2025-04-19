#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(30000, 35000);
    int k = min(gen.uniform(1, n), 100);
    
    cout << n << " " << k << endl;
    for (int i = 1; i <= n; i++) {
        cout << gen.uniform(1, n) << " ";
    }
    return 0;
}
