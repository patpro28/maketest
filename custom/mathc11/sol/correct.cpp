#include <bits/stdc++.h>
using namespace std;

const int MAXA = 1000000;
int spf[MAXA + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // sieve smallest prime factor
    for (int i = 1; i <= MAXA; i++) spf[i] = i;
    for (int i = 2; i * i <= MAXA; i++) {
        if (spf[i] == i) {
            for (long long j = 1LL * i * i; j <= MAXA; j += i)
                if (spf[j] == j) spf[j] = i;
        }
    }

    int N;
    cin >> N;

    unordered_map<int,long long> cnt;

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;

        int kernel = 1;

        while (x > 1) {
            int p = spf[x];
            int c = 0;
            while (spf[x] == p) {
                x /= p;
                c++;
            }
            if (c % 2) kernel *= p;
        }

        cnt[kernel]++;
    }

    long long ans = 0;
    for (auto &p : cnt) {
        long long c = p.second;
        ans += c * (c - 1) / 2;
    }

    cout << ans;
}