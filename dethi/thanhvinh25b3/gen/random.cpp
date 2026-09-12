#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, 10000);
    int k = gen.uniform<int>(1, n);
    
    cout << n << " " << k << "\n";
    for (int i = 1; i <= n; ++i) 
        cout << gen.uniform<long long>(1, 1e12) << " ";
    cout << "\n";
    return 0;
}
