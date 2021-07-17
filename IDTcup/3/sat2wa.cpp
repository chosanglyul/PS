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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
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
int sgn(int n) { return n < 0 ? -1 : 1; }
int _abs(int n) { return n*sgn(n); }
int num(int n) { return _abs(n)-1; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> A(m);
    vector<int> B(n, 0);
    vector<vector<int>> C(n);
    for(auto &i : A) {
        int k; cin >> k;
        i.resize(k);
        for(auto &j : i) {
            cin >> j;
            C[num(j)].push_back(sgn(j));
        }
        if(k == 1) B[num(i[0])] = sgn(i[0]);
    }
    for(int i = 0; i < n; i++) {
        if(C[i].empty()) B[i] = 1;
        else if(C[i].size() == 1 || C[i][0] == C[i][1]) B[i] = C[i][0];
    }
    for(auto &i : A) {
        bool can = false;
        for(auto j : i) {
            if(B[num(j)] == 0 || B[num(j)] == sgn(j))
                can = true;
        }
        if(!can) {
            cout << -1 << "\n";
            return 0;
        }
    }
    for(auto &i : B) {
        if(i < 0) i = 0;
    }
    cout << B;
    return 0;
}