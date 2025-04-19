#include <iostream>
#include <vector>
#include <climits>
#include "random.h"
#include "../params.h"
using namespace std;


int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 1000;
    cout << t << endl;
    for(int i = 0;i < t;i++){
        int a = gen.uniform(1, INT_MAX);
        int b = gen.uniform(1, INT_MAX);
        int k = gen.uniform(1, 82);
        if(a > b) swap(a, b);
        cout << a << " " << b << " " << k << endl;
    }
    return 0;
}
