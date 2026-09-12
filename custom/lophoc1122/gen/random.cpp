#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int p[] = {8, 81, 15625, 5764801};
const int MAX_N = 1e9;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = p[gen.uniform(0, 3)];
    n *= gen.uniform<int>(1, MAX_N / n);
    cout << n << endl;
    
    return 0;
}
