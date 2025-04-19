#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 1000000;
    cout << n << endl;
    int k = gen.uniform(1, max(n / 100, 1));
    
    for (int i = 0, t = 0, u; i < n; i++) {
      if (t == 0) {
        u = gen.uniform(1, 1000000000);
      }
      cout << u << " ";
      t = (t + 1) % k;
    }
    return 0;
}
