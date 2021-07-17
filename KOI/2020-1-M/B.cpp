#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = 1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i+1 << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

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

void dfs(int n, int x, vector<int>& A, vector<vector<int>>& B) {
    B.push_back(A);
    if(++x == n) return;
    for(int i = x; i < n; i++) {
        A.push_back(i);
        dfs(n, i, A, B);
        A.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A;
    vector<vector<int>> B;
    dfs(n, -1, A, B);
    vector<int> C(4);
    for(auto &i : C) cin >> i;
    vector<vector<int>> D(n, vector<int>(5));
    for(auto &i : D) for(auto &j : i) cin >> j;
    int minval = INF, mini = -1;
    for(int i = 0; i < B.size(); i++) {
        vector<int> tmp(5, 0);
        for(auto &j : B[i]) {
            for(int k = 0; k < tmp.size(); k++)
                tmp[k] += D[j][k];
        }
        for(int k = 0; k < tmp.size(); k++) {
            if(k+1 == tmp.size()) {
                if(tmp[k] < minval) {
                    minval = tmp[k];
                    mini = i;
                }
            } else if(tmp[k] < C[k]) break;
        }
    }
    if(mini == -1) cout << -1 << "\n";
    else {
        cout << minval << "\n";
        cout << B[mini];
    }
    return 0;
}