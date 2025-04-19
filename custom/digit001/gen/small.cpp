#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX = 1 << 20;
const int MIN = 1 << 10;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform(1, 1000);
    cout << t << endl;
    for(int i = 0;i < t;i++){
        int a = gen.uniform(1, MIN - 1);
        int b = gen.uniform(1, MAX - 1);
        int k = gen.uniform(1, 82);
        if(a > b) swap(a, b);
        cout << a << " " << b << " " << k << endl;
    }
    return 0;
}
