#include<bits/stdc++.h>
 
using namespace std;
 
const int MOD = 998244353;
 
int n;
 
vector<long long> a;
vector<long long> pa;
vector<long long> ppa;
vector<long long> start;
vector<long long> block;
vector<long long> pblock;
 
vector<long long> prefix_sums(vector<long long> v)
{
 	int k = v.size();
 	vector<long long> res(k + 1);
 	for(int i = 0; i < k; i++) res[i + 1] = res[i] + v[i];
 	return res;
}
 
long long get_partial(int l, int r1, int r2)
{
	// s(l, r1) + s(l, r1 + 1) + ... + s(l, r2 - 1)
 	if(r2 <= r1) return 0ll;
 	int cnt = r2 - r1;
 	long long rem = pa[l] * cnt;
 	long long add = ppa[r2 + 1] - ppa[r1 + 1];
 	return add - rem;
}
 
pair<int, int> convert(long long i)
{
	int idx = upper_bound(start.begin(), start.end(), i) - start.begin() - 1;
	pair<int, int> res = {idx, i - start[idx] + idx};
	return res; 	
}
 
long long query(long long l, long long r)
{
	pair<int, int> lf = convert(l);
	pair<int, int> rg = convert(r);
	long long res = pblock[rg.first + 1] - pblock[lf.first];
	if(lf.second != lf.first) res -= get_partial(lf.first, lf.first, lf.second);
	if(rg.second != n - 1) res -= get_partial(rg.first, rg.second + 1, n);
	return res;	
}
 
int main()
{
	scanf("%d", &n);
	a.resize(n);
	for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
	pa = prefix_sums(a);
	ppa = prefix_sums(pa);
	start = {0};
	for(int i = n; i >= 1; i--)
		start.push_back(start.back() + i);
	block.resize(n);
	for(int i = 0; i < n; i++)
		block[i] = get_partial(i, i, n);
	pblock = prefix_sums(block);
	int q;
	scanf("%d", &q);
	for(int i = 0; i < q; i++)
	{
	 	long long l, r;
	 	scanf("%lld %lld", &l, &r);
	 	printf("%lld\n", query(l - 1, r - 1));
	}
 
}