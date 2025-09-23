#include <bits/stdc++.h>
#define nmax 1000000
#define fast               \
  ios::sync_with_stdio(0); \
  cin.tie(0);              \
  cout.tie(0);
using namespace std;
bool check[nmax + 5];
int sum[nmax + 5];
void prime()
{
  for (int i = 1; i <= nmax; i++)
    check[i] = true;
  check[1] = false;
  for (int i = 1; i <= sqrt(nmax); i++)
    if (check[i])
    {
      for (int j = i * i; j <= nmax; j += i)
        check[j] = false;
    }
}
int main()
{
  fast;
  prime();
  for (int i = 1; i <= nmax; i++)
    sum[i] = sum[i - 1] + check[i];
  int m, l, r;
  cin >> m;
  while (m--)
  {
    cin >> l >> r;
    cout << sum[r] - sum[l - 1] << "\n";
  }
}