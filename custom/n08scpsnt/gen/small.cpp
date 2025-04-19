#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long a = gen.uniform(3LL, N_SML - 2);    
    long long b = gen.uniform(a + 1, N_SML - 1);
    cout << a << " " << b << endl;
    return 0;
}
