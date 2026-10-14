#include <cstdlib>
#include <iostream>
#include "random.h"
using namespace std;
int main(int, char* argv[]) {
    int seed=atoi(argv[1]);
    Random rng(seed);
    int m=rng.uniform(1,seed<10 ? 10 : 150);
    int n=rng.uniform(1,seed<10 ? 10 : 150);
    int probability[]={10,30,50,80,95};
    cout << m << ' ' << n << '\n';
    for (int i=0; i<m; ++i)
        for (int j=0; j<n; ++j)
            cout << (rng.uniform(1,100)<=probability[seed%5]) << (j+1==n ? '\n' : ' ');
}
