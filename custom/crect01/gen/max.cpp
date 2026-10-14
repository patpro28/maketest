#include <cstdlib>
#include <iostream>
#include "random.h"
using namespace std;
int main(int, char* argv[]) {
    int seed=atoi(argv[1]), m=1000, n=1000;
    Random rng(seed);
    if (seed==10) m=1;
    if (seed==11) n=1;
    cout << m << ' ' << n << '\n';
    for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
        bool cell;
        switch(seed) {
            case 0: cell=true; break;
            case 1: cell=false; break;
            case 2: cell=(i+j)%2; break;
            case 3: cell=i%2; break;
            case 4: cell=j%2; break;
            case 5: cell=i>=j; break;
            case 6: cell=i+j>=999; break;
            case 7: cell=!(i==500 && j==500); break;
            case 8: cell=rng.uniform(1,100)<=50; break;
            case 9: cell=rng.uniform(1,100)<=99; break;
            default: cell=true;
        }
        cout << cell << (j+1==n ? '\n' : ' ');
    }
}
