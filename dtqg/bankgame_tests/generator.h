#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include "random.h"
using namespace std;
template<class T> void row(const vector<T>& v) {
    for (int i = 0; i < int(v.size()); ++i) cout << (i ? " " : "") << v[i];
    cout << '\n';
}
int main(int argc, char** argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    Random rng(2026110600ULL + TASK_ID * 1000 + seed);
#if TASK_ID < 4
    const vector<string> edge = {
        "1\n1 1\n1\n1\n", "1\n1 1\n2\n1\n",
        "1\n1 3\n2\n1 1 2\n", "1\n1 3\n1\n1 1 1\n",
        "1\n1 2\n3\n2 2\n", "1\n1 4\n5\n5 5 5 5\n"
    };
    if (seed < 6) { cout << edge[seed]; return 0; }
    int limit = TASK_ID == 2 ? 10 : 20;
    int nlimit = TASK_ID == 0 ? 1 : TASK_ID == 1 ? 2 : limit;
    int vmax = TASK_ID == 1 ? 1000 : 1000000000;
    int t = seed == 27 ? 3 : 1;
    cout << t << '\n';
    for (int z = 0; z < t; ++z) {
        bool large = seed >= 18;
        int m = large ? limit : rng.uniform(1, min(limit, 8));
        int n = rng.uniform(1, min(m, nlimit));
        vector<long long> b(m), a;
        if (seed == 6) { n = min(nlimit, 3); m = max(n, 4); b.assign(m,1); a.assign(n,1); }
        else if (seed == 7) { n = min(nlimit, 2); m = 4; b = {1,1,2,2}; a.assign(n,2); }
        else if (seed == 8) { n = min(nlimit, 3); m = 3; b.assign(m,vmax); a.assign(n,vmax); }
        else if (seed == 9) { n = 1; m = 3; b.assign(m,vmax); a = {vmax-1}; }
        else if (seed == 18) { n = nlimit; b.assign(m,1); a.assign(n,1); }
        else if (seed == 19) { n = min(nlimit, m/2); b.assign(m,1); a.assign(n,m/n); }
        else if (seed == 20) { n = 1; b.assign(m,1); a = {m/2}; }
        else if (seed == 21) { n = nlimit; b.assign(m,vmax); a.assign(n,vmax); }
        else if (seed == 22) {
            n = min(nlimit,2); for (int j = 0; j < m; ++j) b[j] = TASK_ID == 1 ? 50 : 10000000;
            a.assign(n, TASK_ID == 1 ? 1000 : 100000000);
        } else {
            for (auto &v : b) v = rng.uniform(1, large ? (TASK_ID == 1 ? 100 : 10000000) : 9);
            a.assign(n,0);
            // Guarantee a valid allocation before optionally perturbing demands.
            for (int j = 0; j < m; ++j) {
                int project = j < n ? j : rng.uniform(0,n);
                if (project < n) a[project] += b[j];
            }
            if (seed % 4 == 0) a[rng.uniform(0,n-1)] += 1;
            if (seed == 26) { a.assign(n,vmax); }
        }
        cout << n << ' ' << m << '\n'; row(a); row(b);
    }
#else
    const vector<string> edge = {
        "1 1 100\na\na\n", "1 1 1\na\na\n",
        "1 2 100\na\na#\n", "2 2 100\na\na#\n#a\n",
        "1 5 100\na\naaaaa\n", "2 3 2\na\naaa\naaa\n"
    };
    if (seed < 6) { cout << edge[seed]; return 0; }
    int m = seed >= 18 ? 150 : rng.uniform(1, 6);
    int n = seed >= 18 ? 150 : rng.uniform(1, 6);
    if (seed == 6) { m=1; n=6; }
    if (seed == 7) { m=6; n=1; }
    if (seed == 8) { m=2; n=2; }
    if (seed == 9) { m=2; n=3; }
    if (seed == 24) n=149;
    if (seed == 25) n=1;
    if (seed == 26) m=1;
    int mod = seed == 18 ? 1 : seed == 19 ? 1000000000 : seed % 3 == 0 ? 2 : rng.uniform(2,1000000000);
    string s="a";
    vector<string> g(m,string(n,'a'));
    int distance=m+n-2;
    string half(distance/2+1,'a');
    if (seed % 4 == 1) for (int j=0;j<int(half.size());++j) half[j]=char('a'+j%3);
    if (seed % 4 == 2) for (char &c:half)c=char('a'+rng.uniform(0,1));
    if (seed % 4 == 3) for (char &c:half)c=char('a'+rng.uniform(0,2));
    for(int i=0;i<m;++i)for(int j=0;j<n;++j) {
#if TASK_ID == 4
        g[i][j]='a';
#else
        int d=i+j;g[i][j]=half[min(d,distance-d)];
#endif
        if (seed % 5 == 0 && rng.uniform(0,5)==0) g[i][j]='#';
    }
    g[0][0]='a';g[m-1][n-1]='a';
#if TASK_ID == 4
    s="a";
#elif TASK_ID == 5
    s="a";
#elif TASK_ID == 6
    s=seed%4==0?"z":seed%4==1?"b":"a";
#else
    if(seed==6) {g={"abccba"};s="bccb";}
    else if(seed==7) {g={"a","b","c","c","b","a"};s="bc";}
    else if(seed==8) {g={"ab","aa"};s="aba";}
    else if(seed==9) {g={"abc","cba"};s="bb";}
    else if(seed==18) s="a";
    else if(seed==19) s=string(20,'a');
    else if(seed==20) s="aaaaaaaaaaaaaaaaaaab";
    else if(seed==21) s="abcabcabcabcabcabcab";
    else if(seed==22 || seed==23 || seed==24) {
        // Pattern crossing the middle; all diagonal layers read the same word.
        string path=half,tail=half;
        if(distance%2==0)tail.pop_back();
        reverse(tail.begin(),tail.end());path+=tail;
        s=path.substr(max(0,int(half.size())-10),20);
    } else { int length=rng.uniform(1,20);s=string(length,'a');for(char &c:s)c=char('a'+rng.uniform(0,2)); }
#endif
    if(seed==8 && TASK_ID==6) {g={"#a","a#"};s="a";}
    if(seed==9 && TASK_ID==6) {g={"aab","aba"};s="b";}
    if(seed==27) {
#if TASK_ID == 4
        for(int i=1;i<m;++i)g[i][n/2]='#';
#else
        // Nonuniform, high-density binary letters exercise many pair states.
        for(int i=0;i<m;++i)for(int j=0;j<n;++j)g[i][j]=char('a'+rng.uniform(0,1));
        g[0][0]=g[m-1][n-1]='a';
#if TASK_ID == 7
        s="abababababababababaa";
#endif
#endif
    }
    cout<<m<<' '<<n<<' '<<mod<<'\n'<<s<<'\n';for(const auto &line:g)cout<<line<<'\n';
#endif
}
