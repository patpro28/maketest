/*
Author: Tu Pham Anh
Date: 2024/11/21 - 20:35
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const int N = 1e6 + 5;

bool prime[N];

void sang() {
    memset(prime, true, sizeof(prime));
    prime[0] = prime[1] = false;
    for (int i = 2; i * i < N; i++) {
        if (prime[i]) {
            for (int j = i * i; j < N; j += i) {
                prime[j] = false;
            }
        }
    }
}

bool is_beautiful(long long k) {
    string s = to_string(k);
    string revS = s;
    reverse(revS.begin(), revS.end());
    int revK = stoi(revS);
    return s == revS and prime[k] and prime[revK];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    sang();
    long long a, b, ans = 0;
    cin >> a >> b;
    for (long long i = 1; i * i <= b; ++i) 
        if (i * i >= a and is_beautiful(i)) 
            ans++;
    cout << ans << '\n';

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}