#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAXN = 1e6;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    for (int i = 0; i < 3; ++i)
        cout << gen.uniform(1, MAXN) << ' ';
    cout << '\n';
    for (int i = 0; i < 3; ++i)
        cout << gen.uniform(1, MAXN) << ' ';
    
    return 0;
}
