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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<set<int>> H(n), V(m);
    vector<vector<int>> HW(n, {-1}), VW(m, {-1});
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c; cin >> c;
            if(c == '.') {
                H[i].insert(j);
                V[j].insert(i);
            } else {
                HW[i].push_back(j);
                VW[j].push_back(i);
            }
        }
    }
    for(auto &i : HW) i.push_back(m);
    for(auto &i : VW) i.push_back(n);
    pii s, e; cin >> s.fi >> s.se >> e.fi >> e.se;
    --s.fi, --s.se, --e.fi, --e.se;
    queue<pii> Q; Q.push(s);
    H[s.fi].erase(s.se);
    V[s.se].erase(s.fi);
    vector<vector<int>> D(n, vector<int>(m, INF));
    D[s.fi][s.se] = 0;
    while(Q.size()) {
        pii tmp = Q.front(); Q.pop();
        //cout << tmp << " " << D[tmp.fi][tmp.se] << endl;
        
        auto h = upper_bound(HW[tmp.fi].begin(), HW[tmp.fi].end(), tmp.se);
        int hl = max(tmp.se-k, *(h-1)), hh = min(tmp.se+k, *h);
        //cout << hl << " " << hh << endl;
        auto hs = H[tmp.fi].lower_bound(hl), he = H[tmp.fi].upper_bound(hh);
        for(auto iter = hs; iter != he; iter++) {
            Q.push({tmp.fi, *iter});
            V[*iter].erase(tmp.fi);
            D[tmp.fi][*iter] = D[tmp.fi][tmp.se]+1;
        }
        H[tmp.fi].erase(hs, he);

        auto v = upper_bound(VW[tmp.se].begin(), VW[tmp.se].end(), tmp.fi);
        int vl = max(tmp.fi-k, *(v-1)), vh = min(tmp.fi+k, *v);
        //cout << vl << " " << vh << endl;
        auto vs = V[tmp.se].lower_bound(vl), ve = V[tmp.se].upper_bound(vh);
        for(auto iter = vs; iter != ve; iter++) {
            Q.push({*iter, tmp.se});
            H[*iter].erase(tmp.se);
            D[*iter][tmp.se] = D[tmp.fi][tmp.se]+1;
        }
        V[tmp.se].erase(vs, ve);
    }
    cout << (D[e.fi][e.se] == INF ? -1 : D[e.fi][e.se]) << "\n";
    return 0;
}