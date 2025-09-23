#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 100000);
    cout << n << endl;
    cout << "RC55\n";
    n--;
    while (n--) {
        int k = gen.uniform(0, 1);
        if (k == 0) {
            int x = gen.uniform(1, 1000000);
            int y = gen.uniform(1, 1000000);
            cout << "R" << x << "C" << y << '\n';
        } else {
            int x = gen.uniform(1, 1000000);
            int y = gen.uniform(1, 1000000);
            string s = "";
            while (y) {
                char c = 'A' + y % 26;
                s += c;
                y /= 26;
            }
            reverse(s.begin(), s.end());
            cout << s << x << '\n';
        }
    }
    return 0;
}
