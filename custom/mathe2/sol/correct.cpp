#include <bits/stdc++.h>
using namespace std;

/*
    http://math.stackexchange.com/questions/130352/last-non-zero-digit-of-a-factorial
    D(N) = 4D(N/5)D(N%10) if tens digit of N is odd
    D(N) = 6D(N/5)D(N%10) if tens digit of N is even
 */

const int d[] = {1, 1, 2, 6, 4, 2, 2, 4, 2, 8};

int D(int n) {
    if(n < 10) return d[n];
    return (n%100/10%2 ? 4 : 6) * D(n/5)*D(n%10)%10;
}

int main() {
    int n;
    while (std::cin >> n) {
        cout << D(n) << '\n';
    }
    return 0;
}
