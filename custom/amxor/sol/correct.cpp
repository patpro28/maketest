#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
using namespace std;
const int BASE = int(1e9) + 9;

int n, a[100100];
long long f[100100][2], g[100100];

int mostSignificantBit(int n)
{
	for (int i = 29; i >= 0; i--)
		if (n >> i & 1) return i;
	return -1;
}

int dp(vector <int> b, int k, int target)
{
	int n = b.size();
	for (int i = 0; i < n; i++) memset(f[i], 0, sizeof(f[i]));
	
	f[0][0] = (1 << k);
	f[0][1] = b[0] + 1 - (1 << k);
	
	for (int i = 1; i < n; i++)
		for (int u = 0; u < 2; u++)
		{
			f[i][u] += f[i - 1][u] * (1 << k);
			f[i][u] %= BASE;
			f[i][u ^ 1] += f[i - 1][u] * (b[i] + 1 - (1 << k));
			f[i][u ^ 1] %= BASE;
		}
	
	g[n] = 1;
	for (int i = n - 1; i >= 0; i--) g[i] = g[i + 1] * (b[i] + 1 - (1 << k)) % BASE;
	
	long long res = 0;
	for (int i = 0; i < n; i++) 
	{
		long long F = 0;
		int parity = target ^ ((n - 1 - i) % 2);
		if (i) F = f[i - 1][parity];
		else F = parity == 0;
		res += F * g[i + 1];
		res %= BASE;
	}
	
	return int(res % BASE);
}

int main()
{
	//freopen("i.in", "r", stdin);
	int test;
	cin >> test;
	while (test--)
	{
		cin >> n;
		int xorA = 0;
		for (int i = 0; i < n; i++) scanf("%d", a + i), xorA ^= a[i];
		
		long long ans = 1;
		for (int k = 29; k >= 0; k--)
		{
			vector <int> b;
			long long rest = 1;
			
			for (int i = 0; i < n; i++)
				if (a[i] >> k & 1) 
				{
					b.push_back(a[i]);
					a[i] ^= 1 << k;
				}
				else rest = rest * (a[i] + 1) % BASE;
				
			if (b.size() > 1) 
			{
				ans += dp(b, k, xorA >> k & 1) * rest;
				ans %= BASE;
				if ((xorA >> k & 1) != b.size() % 2) break;
			}			
		}
		
		cout << ans << endl;
	}
}
