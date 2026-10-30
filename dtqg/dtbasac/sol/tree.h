#pragma once
#include <algorithm>
#include <array>
#include <iostream>
#include <utility>
#include <vector>
struct Tree {
    int n;
    std::vector<std::vector<std::pair<int,int>>> adj;
    std::vector<int> parent,depth,mask,order,tin,size,heavy;
    explicit Tree(int count):n(count),adj(n+1),parent(n+1),depth(n+1),mask(n+1),tin(n+1),size(n+1,1),heavy(n+1){}
    void read(bool letters=false) {
        for(int i=1;i<n;++i) {
            int u,v,bit=0;std::cin>>u>>v;
            if(letters){char c;std::cin>>c;bit=1<<(c-'a');}
            adj[u].push_back({v,bit});adj[v].push_back({u,bit});
        }
        std::vector<int> pending{1};
        while(!pending.empty()) {
            int u=pending.back();pending.pop_back();tin[u]=int(order.size());order.push_back(u);
            for(auto [v,bit]:adj[u])if(v!=parent[u]) {
                parent[v]=u;depth[v]=depth[u]+1;mask[v]=mask[u]^bit;pending.push_back(v);
            }
        }
        for(int i=n-1;i>=0;--i) {
            int u=order[i];
            for(auto [v,bit]:adj[u])if(parent[v]==u) {
                (void)bit;size[u]+=size[v];
                if(!heavy[u] || size[v]>size[heavy[u]])heavy[u]=v;
            }
        }
    }
    template<class Finish,class Clear> void sack(Finish finish,Clear clear) const {
        std::vector<std::array<int,3>> events{{1,0,1}};
        while(!events.empty()) {
            auto [u,phase,keep]=events.back();events.pop_back();
            if(!phase) {
                events.push_back({u,1,keep});
                if(heavy[u])events.push_back({heavy[u],0,1});
                for(auto [v,bit]:adj[u])if(parent[v]==u && v!=heavy[u]) {
                    (void)bit;events.push_back({v,0,0});
                }
            } else {
                finish(u);if(!keep)clear(u);
            }
        }
    }
    template<class F> void vertices(int u,F action) const {
        for(int i=tin[u];i<tin[u]+size[u];++i)action(order[i]);
    }
    template<class F> void light(int u,F action) const {
        for(auto [v,bit]:adj[u])if(parent[v]==u && v!=heavy[u]){(void)bit;action(v);}
    }
};
