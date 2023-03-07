#include "race.h"
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

int dfs(int x, ll d, int l, vector<vector<pii>> &E,
        vector<int> &len, vector<int> &siz, vector<ll> &dep) {
    siz[x] = 1; len[x] = l; dep[x] = d;
    for(auto &i : E[x]) {
        E[i.fi].erase(find(E[i.fi].begin(), E[i.fi].end(), pii(x, i.se)));
        siz[x] += dfs(i.fi, d+i.se, l+1, E, len, siz, dep);
        if(siz[i.fi] > siz[E[x][0].fi]) swap(i, E[x][0]);
    }
    return siz[x];
}

int val(set<pll> *S, ll k, const pll &x, const pll &i) {
    ll tmp = k+2*x.fi-i.fi;
    auto iter = S->lower_bound({tmp, 0LL});
    if(iter == S->end() || iter->fi != tmp) return INF;
    return iter->se+i.se-2*x.se;
}

int solve(int x, ll k, vector<vector<pii>> &E,
        vector<int> &len, vector<int> &siz, vector<ll> &dep, vector<set<pll>*> &S) {
    if(E[x].empty()) {
        S[x] = new set<pll>;
        S[x]->insert({dep[x], len[x]});
        return INF;
    }

    int ans = INF;
    for(auto &i : E[x]) ans = min(ans, solve(i.fi, k, E, len, siz, dep, S));
    S[x] = S[E[x][0].fi];
    pll tmp = {dep[x], len[x]};
    for(int i = 1; i < E[x].size(); i++) {
        for(auto &j : *S[E[x][i].fi]) ans = min(ans, val(S[x], k, tmp, j));
        for(auto &j : *S[E[x][i].fi]) S[x]->insert(j);
    }
    ans = min(ans, val(S[x], k, tmp, tmp));
    S[x]->insert(tmp);
    return ans;
}

int best_path(int N, int K, int H[][2], int L[]) {
    vector<vector<pii>> E(N);
    for(int i = 0; i+1 < N; i++) {
        E[H[i][0]].push_back({H[i][1], L[i]});
        E[H[i][1]].push_back({H[i][0], L[i]});
    }
    vector<ll> dep(N);
    vector<int> len(N), siz(N);
    dfs(0, 0LL, 0, E, len, siz, dep);
    vector<set<pll>*> S(N, nullptr);
    int ans = solve(0, K, E, len, siz, dep, S);
    if(ans == INF) return -1;
    else return ans;
}

