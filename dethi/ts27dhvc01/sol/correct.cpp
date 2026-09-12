#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, c;
    long long d, e, f;

    cin >> a >> b >> c;
    cin >> d >> e >> f;

    long long s1 = a + b + c;
    long long s2 = d + e + f;

    long long g = gcd(s1, s2);
    long long lcm = s1 / g * s2;

    cout << lcm;

    return 0;
}