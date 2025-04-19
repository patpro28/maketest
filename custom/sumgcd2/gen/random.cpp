#include <bits/stdc++.h>
#include "random.h"
#include "../params.h"
using namespace std;

constexpr int P = 1e9+7;
constexpr int N = 200000;

vector<pair<int, int> > l[N], r[N];
vector<int> ar[N];
map<int, int> g[N], _g[N];
int sum[N], a[N];

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(1, 200000);
    int Q = gen.uniform(1, 1000000);
    cout << n << " " << Q << endl;
    for (int i = 0; i < n; i++) {
        a[i] = gen.uniform(1, 1000000000);
        cout << a[i] << " \n"[i == n - 1];
    }

	for(int i = 0; i < n; i ++) {
		if(i) for(auto [d, c] : l[i - 1]) {
			g[i][__gcd(d, a[i])] = c;
		}
		g[i][a[i]] = i;
		for(auto [d, c] : g[i]) l[i].emplace_back(d, c);

		if(i) sum[i] = sum[i - 1];
		int pre = -1; for(auto [d, c] : l[i]) {
			sum[i] = (sum[i] + 1ll * (c - pre) * d) % P;
			pre = c;
		}
	}
	for(int i = n - 1; i >= 0; i --) {
		if(i < n - 1) for(auto [d, c] : r[i + 1]) {
			_g[i][__gcd(a[i], d)] = c;
		}
		_g[i][a[i]] = i;
		for(auto [d, c] : _g[i]) r[i].emplace_back(d, c);
	}
	
	for(int i = 1; i < n; i ++) {
		ar[i].resize(r[i].size());
		for(int j = r[i].size() - 1; j >= 0; j --) {
			int pre = -1;
			for(auto [d, c] : l[i - 1]) {
				ar[i][j] = (ar[i][j] + 1ll * (c - pre) * __gcd(d, r[i][j].first)) % P;
				pre = c;
			}
		}
	}
	
	int x = 0;
	while(Q --) {
		int L, R;
        do {
            L = gen.uniform(0, n);
            R = gen.uniform(0, n);
        } while ((L + x) % n > (R + x) % n);
        cout << L << " " << R << "\n";
		L = (L + x) % n;R = (R + x) % n;
		if(L == 0) {
			// cout << sum[R] << endl;
			x = sum[R];
			continue;
		}
		else {
			int ans = (sum[R] - sum[L - 1] + P) % P;
			int pre = R + 1, sz = r[L].size();
			for(int i = 0; i < sz; i ++){
			auto [d, c] = r[L][i]; if(c < R + 1){
				ans = ((ans - 1ll * (pre - c) * ar[L][i]) % P + P) % P;
				pre = c;
			}
			}
			// cout << ans << endl;
			x = ans;
		}
	}
}
