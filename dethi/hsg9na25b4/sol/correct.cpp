/*
Author: Tu Pham Anh
Date: 2024/12/11 - 11:28
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;
using score = array<int, 2>;

const int N = 3005;

int n;
vector<int> a;
score dp[N][N];
int first[N], last[N];

score chose(score a, score b, int turn) {
  if (a[turn] > b[turn] || (a[turn] == b[turn] && a[1 - turn] < b[1 - turn])) {
    return a;
  } else {
    return b;
  }
}

// score cal(int l, int r, int turn = 0) {
//   if (l > r) return {0, 0};
//   if (dp[l][r][turn] != -1) return dp[l][r];
//   // Pick left
//   score pick_left = cal(l + 1, r, 1 - turn);
//   if (first[a[l]] == l and last[a[l]] <= r) pick_left[turn]++;
//   // Pick right
//   score pick_right = cal(l, r - 1, 1 - turn);
//   if (last[a[r]] == r and first[a[r]] >= l) pick_right[turn]++;
//   // Choose the best (maximize my score and minimize the opponent's score)
//   dp[l][r] = chose(pick_left, pick_right, turn);
//   return dp[l][r];
// }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);
  cin >> n;
  a.resize(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  memset(first, -1, sizeof first);
  memset(last, -1, sizeof last);
  for (int i = 1; i <= n; ++i)
    if (first[a[i]] == -1)
      first[a[i]] = i;
  for (int i = n; i > 0; --i)
    if (last[a[i]] == -1)
      last[a[i]] = i;

  for (int len = 1; len <= n; ++len) {
    int turn = len % 2;
    for (int l = 1; l + len - 1 <= n; ++l) {
      int r = l + len - 1;
      // Pick left
      score pick_left = dp[l + 1][r];
      if (first[a[l]] == l and last[a[l]] <= r) pick_left[turn]++;
      // Pick right
      score pick_right = dp[l][r - 1];
      if (last[a[r]] == r and first[a[r]] >= l) pick_right[turn]++;
      // Choose the best (maximize my score and minimize the opponent's score)
      dp[l][r] = chose(pick_left, pick_right, turn);
    }
  }

  int turn = n % 2;
  cout << dp[1][n][turn] << ':' << dp[1][n][1 - turn] << '\n';

  return 0;
}