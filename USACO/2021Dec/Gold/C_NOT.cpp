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
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

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

bool topo(vector<vector<int>>& B) {
    int n = B.size();
    vector<int> C(n, 0);
    for(auto &i : B) {
        sort(i.begin(), i.end());
        i.erase(unique(i.begin(), i.end()), i.end());
        for(auto j : i) C[j]++;
    }
    queue<int> Q;
    for(int i = 0; i < n; i++) {
        if(C[i] == 0) Q.push(i);
    }
    while(Q.size()) {
        int tmp = Q.front(); Q.pop();
        for(auto i : B[tmp]) {
            if(--C[i] == 0) Q.push(i);
        }
    }
    for(auto i : C) if(i != 0) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> A(m), B(n), D(n);
        vector<int> E(n, -1);
        vector<bool> st(n, false), ed(n, false);
        bool can = true;
        for(auto &i : A) {
            int k; cin >> k;
            i.resize(k);
            vector<bool> chk(n, false);
            vector<int> sta;
            int lst = -1;
            for(auto &j : i) {
                cin >> j; j--;
                if(chk[j]) {
                    if(sta.back() != j) can = false;
                    else {
                        lst = sta.back();
                        sta.pop_back();
                        if(E[j] != sta.size()) can = false;
                    }
                } else {
                    chk[j] = true;
                    if(sta.size()) B[sta.back()].push_back(j);
                    if(lst != -1) D[lst].push_back(j);
                    if(E[j] == -1) E[j] = sta.size();
                    else if(E[j] != sta.size()) can = false;
                    sta.push_back(j);
                    lst = -1;
                }
            }
            for(int j = 0; j < n; j++) {
                if(chk[j]) {
                    if(ed[j]) can = false;
                    else st[j] = true;
                } else {
                    if(st[j]) ed[j] = true;
                }
            }
        }
        if(can && topo(B) && topo(D)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}