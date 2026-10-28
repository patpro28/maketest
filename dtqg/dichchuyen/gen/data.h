#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
#include "../params.h"

constexpr int KIND = 3;
using ll = long long;
inline int generate(int argc, char **argv, int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rnd(20261027ULL + KIND * 100000ULL + mode * 1000ULL + seed);
    const int sizes[] = {1, 2, 5, 7, 9, 8, 17, 33, 3, 11, 65, 6};
    int n = mode == 0 ? sizes[seed] : mode == 1 ? rnd.uniform(1, 30) :
            mode == 2 ? rnd.uniform(1000, 12000) : int(N_MAX) - (seed == 5);
    int q = mode == 0 ? 40 : mode == 1 ? 150 :
            mode == 2 ? rnd.uniform(1000, 12000) : int(Q_MAX);
    int s = rnd.uniform(1, n), t = rnd.uniform(1, n);
    std::vector<ll> duration(n + 1);
    for (int i = 1; i <= n; ++i)
        duration[i] = (mode == 3 && seed == 1) || (mode == 0 && seed == 5) ?
            1000000000 : rnd.uniform(1, 1000000000);
    std::vector<std::vector<ll>> rows;
    auto ticket = [&](int u, int l, int r, ll c) { rows.push_back({u,l,r,c}); };
    auto dependency = [&](int l, int r, int u) { rows.push_back({l,r,u}); };
    auto portal = [&](int l, int r, int a, int b, ll c) { rows.push_back({l,r,a,b,c}); };
    auto interval = [&]() {
        int l = rnd.uniform(1,n), r = rnd.uniform(1,n);
        if (l > r) std::swap(l,r);
        return std::pair<int,int>{l,r};
    };
    auto cost = [&]() -> ll {
        int type = rnd.uniform(0,4);
        if (type == 0) return 0;
        if (type == 1) return 1000000000;
        return rnd.uniform(1,1000000000);
    };
    auto random_row = [&](int pattern) {
        auto [l,r] = interval();
        if (KIND == 1) ticket(rnd.uniform(1,n),l,r,cost());
        if (KIND == 3) {
            auto [a,b] = interval(); portal(l,r,a,b,cost());
        }
        if (KIND == 2) {
            if (n == 1) { dependency(1,1,1); return; }
            if (pattern % 3 == 0) {
                int u = rnd.uniform(2,n);
                l = rnd.uniform(1,u-1); r = rnd.uniform(l,u-1);
                dependency(l,r,u);
            } else if (pattern % 3 == 1) {
                int u = rnd.uniform(1,n-1);
                l = rnd.uniform(u+1,n); r = rnd.uniform(l,n);
                dependency(l,r,u);
            } else dependency(l,r,rnd.uniform(1,n));
        }
    };
    if (mode == 0) {
        s = 1; t = n;
        if (seed <= 1) {
            if (seed == 1 && KIND == 1) s = n;
            if (seed == 1 && KIND == 2) dependency(1,1,1);
        } else if (seed == 2) {
            if (KIND == 1) ticket(2,1,n,0);
            if (KIND == 2) { dependency(1,1,2); dependency(2,2,3); dependency(3,3,1); }
            if (KIND == 3) portal(2,n-1,1,n,0);
        } else if (seed == 3) {
            s=n; t=1;
            if (KIND == 1) { ticket(n,1,1,3); ticket(1,2,n-1,2); }
            if (KIND == 3) portal(1,1,n,n,0);
        } else if (seed == 4) {
            s=n/2;
            if (KIND == 1) ticket(s,1,n,0);
            if (KIND == 3) portal(1,n,1,n,0);
            if (KIND == 2) for (int u=2;u<=n;++u) dependency(1,u-1,u);
        } else if (seed == 5) {
            for (int u=1;u<n;++u) {
                if (KIND == 1) ticket(u,u+1,u+1,1000000000);
                if (KIND == 2) dependency(u,u,u+1);
                if (KIND == 3) portal(u,u,u+1,u+1,1000000000);
            }
        } else if (seed == 6) {
            if (KIND == 1) {
                ticket(1,2,n,50); ticket(1,2,n,7); ticket(n,1,n,0);
            }
            if (KIND == 2) for (int repeat=0;repeat<4;++repeat) {
                dependency(1,8,9); dependency(4,9,17);
            }
            if (KIND == 3) {
                portal(1,1,2,2,20); portal(1,1,n-1,n-1,7); portal(2,n-1,n,n,0);
            }
        } else if (seed == 7) {
            for (int i=0;i<q;++i) {
                if (KIND == 1) ticket(1,2,n-1,q-i);
                if (KIND == 2) dependency(n/2,n,i % (n/2-1)+1);
                if (KIND == 3) portal(1,1,2,n,q-i);
            }
        } else if (seed == 8) {
            if (KIND == 1) { ticket(1,2,2,10); ticket(1,3,3,1); ticket(3,2,2,1); }
            if (KIND == 2) dependency(1,n,2);
            if (KIND == 3) { t=2; portal(1,1,2,2,10); portal(1,1,3,3,1); portal(3,3,2,2,1); }
        } else if (seed == 9) {
            for (int u=1;u<=n;++u) {
                int v=u%n+1;
                if (KIND == 1) ticket(u,v,v,0);
                if (KIND == 2 && u<n) dependency(u,u,u+1);
                if (KIND == 3) portal(u,u,v,v,0);
            }
            if (KIND == 2) dependency(n,n,1);
        } else if (seed == 10) {
            if (KIND == 1) { ticket(1,2,n-1,3); ticket(n-1,n,n,4); }
            if (KIND == 2) { dependency(1,n-2,n-1); dependency(2,n-1,n); }
            if (KIND == 3) { portal(1,1,2,2,5); portal(2,n-1,2,n-1,0); portal(n-1,n-1,n,n,7); }
        } else {
            s=n; t=n;
            if (KIND == 1) { ticket(n,n,n,0); ticket(1,2,n-1,0); }
            if (KIND == 2) dependency(2,n,n);
            if (KIND == 3) { portal(1,2,3,4,0); portal(3,4,1,2,1); }
        }
    } else if (mode == 3 && seed == 1) {
        s=1; t=n;
        for (int u=1;u<n;++u) {
            if (KIND == 1) ticket(u,u+1,u+1,1000000000);
            if (KIND == 2) dependency(u,u,u+1);
            if (KIND == 3) portal(u,u,u+1,u+1,1000000000);
        }
        while (int(rows.size())<q) {
            if (KIND == 1) ticket(n,n,n,0);
            if (KIND == 2) dependency(1,n-1,n);
            if (KIND == 3) portal(n,n,n,n,0);
        }
    } else if (mode == 3 && seed == 2) {
        s=1; t=n;
        for (int i=0;i<q;++i) {
            if (KIND == 1) ticket(1,1,n,i==q-1 ? 0 : cost());
            if (KIND == 2) dependency(1,n,i%n+1);
            if (KIND == 3) portal(1,n,1,n,i==q-1 ? 0 : cost());
        }
    } else if (mode == 3 && seed == 3) {
        s=1; t=n;
        for (int i=0;i<q;++i) {
            if (KIND == 1) ticket(i%n+1,2,n-1,cost());
            if (KIND == 2) dependency(2,n-1,(i%2 ? 1 : n));
            if (KIND == 3) {
                if (i==0) portal(1,1,2,2,1);
                else if (i==q-1) portal(n-1,n-1,n,n,1);
                else portal(2,n-1,2,n-1,cost());
            }
        }
    } else if (mode == 3 && seed == 4) {
        s=1; t=n;
        for (int i=0;i<q;++i) {
            if (KIND == 1) ticket(rnd.uniform(2,n),1,n,cost());
            if (KIND == 2) random_row(1);
            if (KIND == 3) portal(2,n,2,n,cost());
        }
    } else {
        for (int i=0;i<q;++i) random_row(seed);
    }
    q=int(rows.size());
    if (KIND == 1) std::printf("%d %d %d\n",n,q,s);
    if (KIND == 2) {
        std::printf("%d %d\n",n,q);
        for (int i=1;i<=n;++i) std::printf("%lld%c",duration[i],i==n?'\n':' ');
    }
    if (KIND == 3) std::printf("%d %d %d %d\n",n,q,s,t);
    for (const auto &row:rows)
        for (size_t j=0;j<row.size();++j) std::printf("%lld%c",row[j],j+1==row.size()?'\n':' ');
    return 0;
}
