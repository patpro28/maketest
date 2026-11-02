// Independent references for test auditing. Not a contestant solution.
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc,char **argv) {
    if(argc!=2) return 1;
    int code=atoi(argv[1]),n,m,p=0,k=0;
    long long penalty=0,w[26]={};
    char target=0;
    string a,b,d;
    cin>>n>>m;
    if(code==250) cin>>p;
    if(code==231 || code==252) cin>>k;
    if(code==252) cin>>penalty;
    cin>>a>>b;
    if(code==250) cin>>d;
    if(code==202) cin>>target;
    if(code==230 || code==252) for(auto &x:w) cin>>x;
    if(code==203) reverse(b.begin(),b.end());

    if(code==250) {
        auto possible=[&](int length) {
            unordered_set<string> first,second;
            for(int i=0;i+length<=n;++i) first.insert(a.substr(i,length));
            for(int j=0;j+length<=m;++j) {
                string text=b.substr(j,length);
                if(first.count(text)) second.insert(text);
            }
            for(int h=0;h+length<=p;++h) if(second.count(d.substr(h,length))) return true;
            return false;
        };
        int low=0,high=min(n,min(m,p));
        while(low<high) {
            int middle=(low+high+1)/2;
            if(possible(middle)) low=middle;
            else high=middle-1;
        }
        cout<<low<<'\n';return 0;
    }

    if(code==251) {
        // Forward DP of "best first piece" and "ending second piece".
        vector<int> previous_end(m+1),previous_best(m+1),previous_two(m+1,-1);
        int answer=-1;
        for(int i=1;i<=n;++i) {
            vector<int> ending(m+1),best(m+1),two(m+1,-1);
            for(int j=1;j<=m;++j) {
                if(a[i-1]==b[j-1]) {
                    ending[j]=previous_end[j-1]+1;
                    if(previous_two[j-1]>=0) two[j]=previous_two[j-1]+1;
                    if(previous_best[j-1]>0) two[j]=max(two[j],previous_best[j-1]+1);
                }
                best[j]=max(ending[j],max(previous_best[j],best[j-1]));
                answer=max(answer,two[j]);
            }
            previous_end.swap(ending);previous_best.swap(best);previous_two.swap(two);
        }
        cout<<answer<<'\n';return 0;
    }

    long long answer=0;
    int best_a=0,best_b=0;
    for(int offset=1-m;offset<n;++offset) {
        int start_a=max(offset,0),start_b=max(-offset,0),length=min(n-start_a,m-start_b);
        int run=0;bool contains=false;
        long long best_ending=0,prefix=0;
        deque<int> errors;
        deque<pair<int,long long> > minimum;
        minimum.push_back(make_pair(0,0));
        int left=0;
        for(int pos=0;pos<length;++pos) {
            char x=a[start_a+pos],y=b[start_b+pos];
            if(code==231 || code==252) {
                if(x!=y) errors.push_back(pos+1);
                if((int)errors.size()>k) { left=errors.front();errors.pop_front(); }
                if(code==231) answer=max(answer,(long long)pos+1-left);
                else {
                    prefix+=x==y ? w[x-'a'] : -penalty;
                    while(!minimum.empty() && minimum.front().first<left) minimum.pop_front();
                    if(!minimum.empty()) answer=max(answer,prefix-minimum.front().second);
                    while(!minimum.empty() && minimum.back().second>=prefix) minimum.pop_back();
                    minimum.push_back(make_pair(pos+1,prefix));
                }
                continue;
            }
            if(x!=y) { run=0;contains=false;best_ending=0;continue; }
            ++run;contains=contains || x==target;
            if(code==232) answer+=run;
            else if(code==230) {
                best_ending=max(0LL,best_ending+w[x-'a']);answer=max(answer,best_ending);
            } else if(code==201) {
                int i=start_a+pos-run+2,j=start_b+pos-run+2;
                if(run>answer || (run==answer && (i<best_a || (i==best_a && j<best_b)))) {
                    answer=run;best_a=i;best_b=j;
                }
            } else if(code!=202 || contains) answer=max(answer,(long long)run);
        }
    }
    if(code==201) cout<<answer<<' '<<best_a<<' '<<best_b<<'\n';
    else cout<<(code==202 && answer==0 ? -1 : answer)<<'\n';
}
