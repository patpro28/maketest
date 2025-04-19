#include <iostream>
#include <vector>
#include <climits>
#include "random.h"
#include "../params.h"
using namespace std;

const int MIN = 1 << 10;

int main(int, char* argv[]) {

    int seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 1000;
    cout << t << endl;
    for(int i = 0;i < t;i++){
        int a = gen.uniform(1, MIN - 1);
        int b = gen.uniform(1, INT_MAX);
        int k = gen.uniform(1, 82);
        if(a > b) swap(a, b);
        cout << a << " " << b << " " << k << endl;
    }
    return 0;
}
