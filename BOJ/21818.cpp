#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

void dfs(int x, int y, int n, int m, vector<vector<int>> &D, vector<int> &T) {
    if(y == m) {
        D.push_back(T);
        return;
    }
    for(int i = x; i < n; i++) {
        T.push_back(i);
        dfs(i+1, y+1, n, m, D, T);
        T.pop_back();
    }
}

void solve(const vector<int> &A, vector<int> &T, vector<int> &C, vector<piii> &ans) {
    int n = C.size();
    vector<int> E(n);
    for(int i = 0; i < n; i++) E[i] = A[T[i]];
    piii tmp = {0, {0, 0}};
    for(int i = 0; i < n; i++) {
        if(E[i] == 1) tmp.fi = C[i];
        else if(E[i] == 2) tmp.se.fi = C[i];
        else if(E[i] == 4) tmp.se.se = C[i];
    }
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if((E[i] | E[j]) == E[j]) {
                int tt = E[j]-E[i];
                if(tt == 1) tmp.fi = C[j]-C[i];
                else if(tt == 2) tmp.se.fi = C[j]-C[i];
                else if(tt == 4) tmp.se.se = C[j]-C[i];
            }
        }
    }

    if(tmp.fi <= 0 || tmp.se.fi <= 0 || tmp.se.se <= 0) return;
    if(tmp.fi > tmp.se.fi || tmp.fi > tmp.se.se || tmp.se.fi > tmp.se.se) return; 

    for(int i = 0; i < n; i++) {
        int tt = 0;
        if(E[i]&1) tt += tmp.fi;
        if(E[i]&2) tt += tmp.se.fi;
        if(E[i]&4) tt += tmp.se.se;
        if(C[i] != tt) return;
    }
    ans.push_back(tmp);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    const vector<int> A = {1, 2, 4, 3, 5, 6, 7}, B = {1, 2, 3, 4, 5, 6, 7};
    vector<vector<int>> D[4];
    vector<int> TT;
    for(int i = 4; i <= 7; i++) {
        dfs(0, 0, 7, i, D[i-4], TT);
        // cout << D[i-4].size() << endl << " " << D[i-4] << endl;
    }
    while(t--) {
        int n; cin >> n;
        vector<int> C(n);
        for(auto &i : C) cin >> i;
        sort(C.begin(), C.end());
        vector<piii> ans;
        for(auto &T : D[n-4]) {
            solve(A, T, C, ans);
            solve(B, T, C, ans);
        }
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        // cout << ans << endl;
        cout << ans.size() << "\n";
    }
    return 0;
}
