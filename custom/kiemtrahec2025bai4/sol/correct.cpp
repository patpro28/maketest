#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int W = 2e5 + 5;

ll n, m, k, a[W];

bool hyh(ll x){
  ll sum = 0;
  for (int i = 1; i <= n; i++){
    sum += min(a[i], x);
  }
  return sum / k >= x;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> k ;
  for (int i = 1; i  <= n; i++){
    cin >> a[i];
  }
  ll l = 1, r = 1e18;
  while (l < r) {
    ll mid = (l + r + 1) >> 1;
    hyh(mid) ? l = mid : r = mid - 1;
  }
  cout << l;
	return 0;
}
