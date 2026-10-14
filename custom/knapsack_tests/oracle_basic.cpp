// Independent sparse-state and grouped-polynomial references for large cases.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;

void maximize(bool exact) {
    int n,capacity; scanf("%d%d",&n,&capacity);
    map<int,long long> states; states[0]=0;
    for(int i=0;i<n;++i) {
        int weight; long long value; scanf("%d%lld",&weight,&value);
        auto next=states;
        for(auto state:states) if(state.first+weight<=capacity) {
            int new_weight=state.first+weight;
            auto it=next.find(new_weight);
            if(it==next.end()) next[new_weight]=state.second+value;
            else it->second=max(it->second,state.second+value);
        }
        if(!exact) {
            // Dominated states can be removed only for the at-most-capacity problem.
            long long best=-1;
            for(auto it=next.begin();it!=next.end();) {
                if(it->second<=best) it=next.erase(it);
                else { best=it->second; ++it; }
            }
        }
        states.swap(next);
    }
    if(exact) {
        auto found=states.find(capacity);
        printf("%lld\n",found==states.end() ? -1LL : found->second);
    } else {
        long long answer=0; for(auto state:states) answer=max(answer,state.second);
        printf("%lld\n",answer);
    }
}

void count_subsets() {
    int n,target; scanf("%d%d",&n,&target); map<int,int> groups;
    for(int i=0;i<n;++i) { int a; scanf("%d",&a); ++groups[a]; }
    const int MOD=1000000007;
    vector<vector<int>> choose(n+1,vector<int>(n+1,0)); choose[0][0]=1;
    for(int i=1;i<=n;++i) {
        choose[i][0]=1;
        for(int k=1;k<=i;++k) choose[i][k]=(choose[i-1][k-1]+choose[i-1][k])%MOD;
    }
    vector<int> coefficients(target+1,0); coefficients[0]=1;
    for(auto group:groups) {
        int value=group.first,multiplicity=group.second;
        auto next=coefficients;
        for(int k=1;k<=multiplicity && k*value<=target;++k) {
            int shift=k*value;
            for(int s=0;s+shift<=target;++s) {
                next[s+shift]=(next[s+shift]+1LL*coefficients[s]*choose[multiplicity][k])%MOD;
            }
        }
        coefficients.swap(next);
    }
    printf("%d\n",coefficients[target]);
}

int main(int argc,char **argv) {
    if(argc!=2) return 1;
    int problem=atoi(argv[1]);
    if(problem==0 || problem==4) maximize(problem==4);
    else if(problem==3) count_subsets();
    else return 1;
}
