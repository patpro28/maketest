#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m, l, q;
    set<int> a, b, c;
    cin >> n;
    for(int i = 0; i < n; ++i){
        int v;
        cin >> v;
        a.insert(v);
    }
    cin >> m;
    for(int i = 0; i < m; ++i){
        int v;
        cin >> v;
        b.insert(v);
    }
    cin >> l;
    for(int i = 0; i < l; ++i){
        int v;
        cin >> v;
        c.insert(v);
    }
    set<int> memo;
    for(auto v1 : a){
        for(auto v2 : b){
            for(auto v3 : c){
                memo.insert(v1 + v2 + v3);
            }
        }
    }
    
    cin >> q;
    for(int i = 0; i < q; ++i){
        int x;
        cin >> x;
        if(memo.find(x) == memo.end()){
            cout << "No" << endl;
        }else{
            cout <<"Yes" << endl;
        }
    }
}