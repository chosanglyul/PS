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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

/* https://github.com/justiceHui/AlgorithmImplement/blob/master/Math/ExtendGCD.cpp */
ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) { //return x when ax mod m = 1, fail -> -1
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int l(int i, vector<int> &L, int t) { return min(i-L[i]-1, t); }
int r(int i, vector<int> &R, int t) { return min(R[i]-i-1, t); }

struct RMQ {
    vector<vector<int>> sparse;
    
    int query(int s, int e) {
        if(s >= e) return -INF;
        int idx = __lg(e-s);
        return max(sparse[idx][s], sparse[idx][e-(1<<idx)]);
    }

    RMQ(vector<int> &A) {
        sparse.resize(__lg(A.size())+1);
        sparse[0] = A;
        for(int i = 1; i < sparse.size(); i++) {
            sparse[i].resize(A.size());
            for(int j = 0; j+(1<<(i-1)) < A.size(); j++)
                sparse[i][j] = max(sparse[i-1][j], sparse[i-1][j+(1<<(i-1))]);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        cout << "Case #" << _t+1 << endl;
        int n; cin >> n;
        vector<bool> A(n);
        for(int i = 0; i < n; i++) {
            int x; cin >> x;
            A[i] = (x == 2);
        }
        
        vector<int> L(n, -1), R(n, n);
        for(int i = 0, j = -1; i < n; i++) {
            L[i] = j;
            if(A[i]) j = i;
        }
        for(int i = n-1, j = n; i >= 0; i--) {
            R[i] = j;
            if(A[i]) j = i;
        }

        int m, t; cin >> m >> t;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int ans = 0;
        for(int i = 0; i < n; i++) {
            dp[0][i] = l(i, L, t)+r(i, R, t)+1;
            ans = max(ans, dp[0][i]);
        }
        RMQ rmq(dp[0]);

        for(int k = 1; k < m; k++) {
            for(int i = 0; i < n; i++) {
                int jj = max(0, i-2*t-1);
                if(jj >= L[i]) dp[k][i] = dp[k-1][jj]+r(i, R, t)+min(i-jj-1, 2*t)+1-r(jj, R, t);

                if(L[i] >= 0) {
                    dp[k][i] = max(dp[k][i], dp[k-1][L[i]]+r(i, R, t)+min(i-L[i]-1, 2*t)+1-r(L[i], R, t));
                    
                    int tmp, l2 = max(0, L[L[i]]);
                    if(i-L[i] <= t) {
                        int cut = max(l2, L[i]-t);
                        tmp = rmq.query(cut, L[i]);
                        dp[k][i] = max(dp[k][i], tmp+r(i, R, t)+i-L[i]+1);

                        tmp = rmq.query(l2, cut);
                        dp[k][i] = max(dp[k][i], tmp+r(i, R, t)+l(i, L, t)+1);
                    } else {
                        tmp = rmq.query(l2, L[i]);
                        dp[k][i] = max(dp[k][i], tmp+r(i, R, t)+l(i, L, t)+1);
                    }

                    tmp = rmq.query(0, l2);
                    dp[k][i] = max(dp[k][i], tmp+r(i, R, t)+l(i, L, t)+1);
                }
                
                ans = max(ans, dp[k][i]);
            }

            rmq = RMQ(dp[k]);
        }

        cout << ans;
        cout << endl;
    }
    return 0;
}
