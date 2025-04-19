#include <bits/stdc++.h>

#define bug(x) cerr << #x << " " << x << endl

#define endl "\n"
#define ll long long
#define mp make_pair
using namespace std;
constexpr int P = 1e9+7;
constexpr int N = 200000;

vector<pair<int, int> > l[N], r[N];
vector<int> ar[N];
map<int, int> g[N], _g[N];
int sum[N], a[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, Q; cin >> n >> Q;

	for(int i = 0; i < n; i ++) cin >> a[i];

	for(int i = 0; i < n; i ++) {
		if(i) for(auto [d, c] : l[i - 1]) {
			g[i][__gcd(d, a[i])] = c;
		}
		g[i][a[i]] = i;
		for(auto [d, c] : g[i]) l[i].emplace_back(mp(d, c));

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
		for(auto [d, c] : _g[i]) r[i].emplace_back(mp(d, c));
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
		int L, R; cin >> L >> R;
		L = (L + x) % n;R = (R + x) % n;
		if(L == 0) {
			cout << sum[R] << endl;
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
			cout << ans << endl;
			x = ans;
		}
	}
	
	
	return 0;
}