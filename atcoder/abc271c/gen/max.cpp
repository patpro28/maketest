#include <cstdlib>
#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;
int main(int, char* argv[]) {
    int seed = atoi(argv[1]);
    Random rng(seed);
    int n = N_MAX - (seed == 11);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        switch(seed) {
            case 0: a[i] = i+1; break;
            case 1: a[i] = n-i; break;
            case 2: a[i] = 1; break;
            case 3: a[i] = A_MAX; break;
            case 4: a[i] = i+2; break;
            case 5: a[i] = 2*i+1; break;
            case 6: a[i] = i/2+1; break;
            case 7: a[i] = rng.uniform(1,n); break;
            case 8: a[i] = rng.uniform(1,(int)A_MAX); break;
            case 9: a[i] = i < n/2 ? i+1 : A_MAX; break;
            case 10: a[i] = i+1 == n/2 ? A_MAX : i+1; break;
            default: a[i] = 2;
        }
    }
    cout << n << '\n';
    for (int i = 0; i < n; ++i) cout << a[i] << (i+1 == n ? '\n' : ' ');
}
