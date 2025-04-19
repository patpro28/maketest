#include <bits/stdc++.h>

using namespace std;

//---------- Define ------------
#define ll long long
#define ld long double
//------------------------------
#define pii pair <int, int>
#define pli pair <ll, int>
#define pil pair <int, ll>
#define pll pair <ll, ll>
#define fi first
#define se second
//------------------------------
#define tupi tuple <int, int, int>
//------------------------------
#define inf 0x3f3f3f3f

//----------- Const ------------
const ll nx = 1e6+9;
const ll bx = 4e6+9;
const ll kx = 1e3+9;
const ll mod = 1e9+7;

//------ Declare Variable ------
ll t, n;

struct matrix{
    ll c[19][19];
    matrix(){
        for (int i = 1; i <= 2; i++){
            for (int j = 1; j <= 2; j++){
                c[i][j] = 0;
            }
        }
    }
};

matrix operator * (matrix a, matrix b){
    matrix res;
    for (int i = 1; i <= 2; i++){
        for (int j = 1; j <= 2; j++){
            res.c[i][j] = 0;
            for (int t = 1; t <= 2; t++){
                (res.c[i][j] += a.c[i][t] * b.c[t][j] + mod) %= mod;
            }
        }
    }
    return res;
}

//---------- Function ----------
matrix mu(matrix a, ll m){
    matrix res;
    for (int i = 1; i <= 2; i++){
        res.c[i][i] = 1;
    }
    for ( ; m > 0; a = a * a, m >>= 1){
        if (m % 2 == 1){
            res = res * a;
        }
    }
    return res;
}

//------------ Main ------------
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> t;
    while(t--){
        cin >> n;
        if (n == 1){cout << 0 << "\n"; continue;}
        if (n == 2){cout << 1 << "\n"; continue;}
        // if (n == 3){cout << 5 << "\n"; continue;}
        matrix pw;
        pw.c[1][1] = 3; pw.c[1][2] = -1;
        pw.c[2][1] = 1;
        matrix cs;
        cs.c[1][1] = 3; cs.c[2][1] = 1;
        pw = mu(pw, n-2);
        pw = pw * cs;
        cout << (pw.c[1][1] - n + mod) % mod << "\n";
    }
}