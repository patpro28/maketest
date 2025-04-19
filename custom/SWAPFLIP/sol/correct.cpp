#include <bits/stdc++.h>
using namespace std;
#define  endl "\n"

int32_t main() {
	
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
	int T;
	cin>> T;
	while(T--){
	    int n;
	    cin>>n;
	    string s, t;
	    cin>>s>>t;
	    
	    int cnt = 0;
	    
	    for(int i = 0; i < n; i++){
	        if(s[i] != t[i]) cnt++;
	    }
	    
	    if(cnt & 1){
	        cout<<"NO"<<endl;
	    }
	    else{
	        cout<<"YES"<<endl;
	    }
	    
	}
	return 0;
}