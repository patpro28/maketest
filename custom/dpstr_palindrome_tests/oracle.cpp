#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
const int MOD=1000000007;
int main(int argc,char **argv) {
    if(argc!=2) return 1;
    int code=atoi(argv[1]),n,q=0,k=0;string s;
    cin>>n;
    if(code==600) cin>>q;
    if(code==651) cin>>k;
    cin>>s;
    if(code<=602) {
        vector<int> odd(n),even(n);
        for(int i=0,l=0,r=-1;i<n;++i) {
            int h=i>r?1:min(odd[l+r-i],r-i+1);
            while(i-h>=0 && i+h<n && s[i-h]==s[i+h]) ++h;
            odd[i]=h;
            if(i+h-1>r) { l=i-h+1;r=i+h-1; }
        }
        for(int i=0,l=0,r=-1;i<n;++i) {
            int h=i>r?0:min(even[l+r-i+1],r-i+1);
            while(i-h-1>=0 && i+h<n && s[i-h-1]==s[i+h]) ++h;
            even[i]=h;
            if(i+h-1>r) { l=i-h;r=i+h-1; }
        }
        if(code==600) {
            while(q--) {
                int l,r;cin>>l>>r;--l;--r;
                int len=r-l+1,c=(l+r+1)/2;
                bool ok=len%2?odd[c]>=len/2+1:even[c]>=len/2;
                cout<<(ok?"YES":"NO")<<'\n';
            }
        } else if(code==601) {
            int length=0,start=0;
            auto offer=[&](int len,int at) { if(len>length || (len==length && at<start)) { length=len;start=at; } };
            for(int i=0;i<n;++i) { offer(2*odd[i]-1,i-odd[i]+1);offer(2*even[i],i-even[i]); }
            cout<<length<<' '<<start+1<<'\n';
        } else {
            long long total=0;
            for(int i=0;i<n;++i) total+=odd[i]+even[i];
            cout<<total<<'\n';
        }
        return 0;
    }
    if(code==603 || code==630) {
        string t(s.rbegin(),s.rend());vector<int> f(n+1);
        for(char x:s) {
            int diagonal=0;
            for(int j=1;j<=n;++j) {
                int old=f[j];f[j]=x==t[j-1]?diagonal+1:max(f[j],f[j-1]);diagonal=old;
            }
        }
        cout<<(code==603?f[n]:n-f[n])<<'\n';return 0;
    }
    if(code==631 || code==650) {
        vector<long long> del(n),change(n);
        if(code==631) for(auto &x:del) cin>>x;
        else for(int i=0;i<n;++i) cin>>del[i]>>change[i];
        vector<long long> prev(n),cur(n);
        for(int r=0;r<n;++r) {
            cur[r]=del[r];
            for(int l=r-1;l>=0;--l) {
                long long benefit=max(prev[l],cur[l+1]);
                if(s[l]==s[r] || code==650) {
                    long long price=s[l]==s[r]?0:min(change[l],change[r]);
                    benefit=max(benefit,(l+1<r?prev[l+1]:0)+del[l]+del[r]-price);
                }
                cur[l]=benefit;
            }
            prev.swap(cur);
        }
        cout<<accumulate(del.begin(),del.end(),0LL)-prev[0]<<'\n';return 0;
    }
    if(code==632) {
        vector<int> prev(n),cur(n);
        for(int r=0;r<n;++r) {
            long long added=1;cur[r]=1;
            for(int l=r-1;l>=0;--l) {
                if(s[l]==s[r]) added=(added+1+prev[l+1])%MOD;
                cur[l]=int((prev[l]+added)%MOD);
            }
            prev.swap(cur);
        }
        cout<<prev[0]<<'\n';return 0;
    }
    if(code==651) {
        // Minimize deletions for each replacement budget, storing complete intervals.
        vector<uint16_t> prev(n*n),cur(n*n);
        for(int t=0;t<=k;++t) {
            for(int l=n-1;l>=0;--l) {
                cur[l*n+l]=0;
                for(int r=l+1;r<n;++r) {
                    int best=1+min(cur[(l+1)*n+r],cur[l*n+r-1]);
                    if(s[l]==s[r]) best=min(best,l+1<r?int(cur[(l+1)*n+r-1]):0);
                    else if(t) best=min(best,l+1<r?int(prev[(l+1)*n+r-1]):0);
                    cur[l*n+r]=uint16_t(best);
                }
            }
            prev.swap(cur);
        }
        cout<<n-prev[n-1]<<'\n';return 0;
    }
    // Count distinct strings by their outer character and widest possible endpoints.
    vector<array<int,26>> next(n+1),last(n+1);
    next[n].fill(n);last[0].fill(-1);
    for(int i=n-1;i>=0;--i) { next[i]=next[i+1];next[i][s[i]-'a']=i; }
    for(int i=0;i<n;++i) { last[i+1]=last[i];last[i+1][s[i]-'a']=i; }
    vector<int> f(n*n);
    for(int len=1;len<=n;++len) for(int l=0;l+len<=n;++l) {
        int r=l+len-1;long long count=0;
        for(int c=0;c<26;++c) {
            int p=next[l][c],qpos=last[r+1][c];
            if(p>qpos) continue;
            ++count;
            if(p<qpos) count+=1+(p+1<qpos?f[(p+1)*n+qpos-1]:0);
        }
        f[l*n+r]=int(count%MOD);
    }
    cout<<f[n-1]<<'\n';
}
