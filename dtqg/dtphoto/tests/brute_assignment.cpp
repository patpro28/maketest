// Enumerate all 5^n assignments and recover the order by topological sorting.
// Does not use majority voting. Only for n <= 8.
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
int n, photo[5][8], moved[9];
vector<int> answer;
void check_assignment(){
    int next[9][5], degree[9]{}, indegree[9]{}, queue[9], head=0, tail=0;
    for(int k=0;k<5;++k){
        int previous=0;
        for(int i=0;i<n;++i){
            int x=photo[k][i];
            if(moved[x]==k)continue;
            if(previous){
                next[previous][degree[previous]++]=x;
                ++indegree[x];
            }
            previous=x;
        }
    }
    for(int x=1;x<=n;++x)if(!indegree[x])queue[tail++]=x;
    while(head<tail){
        int x=queue[head++];
        for(int i=0;i<degree[x];++i){
            int y=next[x][i];
            if(--indegree[y]==0)queue[tail++]=y;
        }
    }
    if(tail<n)return;
    vector<int> candidate(queue,queue+n);
    if(answer.empty())answer=candidate;
    else assert(answer==candidate);
}
void enumerate_assignments(int x){
    if(x>n){check_assignment();return;}
    for(int k=0;k<5;++k){
        moved[x]=k;
        enumerate_assignments(x+1);
    }
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;assert(n>=1 && n<=8);
    for(int k=0;k<5;++k)for(int i=0;i<n;++i)cin>>photo[k][i];
    // Visit every assignment to exercise the full bound and check uniqueness.
    // A contest solution can stop at the first acyclic graph.
    enumerate_assignments(1);
    if(answer.empty()){cout<<"IMPOSSIBLE\n";return 0;}
    for(int i=0;i<n;++i)cout<<(i?" ":"")<<answer[i];cout<<'\n';
}
