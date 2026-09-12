#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;
int a[N], p[N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  p[n] = a[n];
  for (int i = n - 1; i >= 1; --i) p[i] = min(p[i + 1], a[i]);
  for (int i = 1; i <= n; ++i) {
    int j = lower_bound(p + i + 1, p + n + 1, a[i]) - p - 1;
    cout << j - i << ' ';
  }
  return 0;
}
