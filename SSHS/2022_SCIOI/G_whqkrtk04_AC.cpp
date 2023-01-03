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
 
typedef struct res {
    vector<int> A;
    ll ans = 0LL;
} res;
 
void dfs(int x, vector<vector<int>>& E, vector<int>& D) {
    int ma = 0;
    for(auto i : E[x]) {
        dfs(i, E, D);
        ma = max(ma, D[i]);
    }
    sort(E[x].begin(), E[x].end(), [&](int a, int b) {
        return D[a] > D[b];
    });
    D[x] = ++ma;
}
 
void solve(int x, vector<vector<int>>& E, vector<res*>& R) {
    for(auto i : E[x]) solve(i, E, R);
    if(E[x].empty()) R[x] = new res();
    else R[x] = R[E[x][0]];

    int siz = 0;
    if(E[x].size() > 1) siz = R[E[x][1]]->A.size();
    vector<pll> U(siz, {1LL, 0LL});
 
    for(auto i : E[x]) {
        vector<int>& T = R[i]->A;
        auto jter = U.rbegin();
        for(auto iter = T.rbegin(); iter != T.rend() && jter != U.rend(); iter++, jter++) {
            (*jter).fi = ((*jter).fi*(*iter+1LL))%P;
            (*jter).se += *iter;
        }
    }
 
    for(int i = 1; i < E[x].size(); i++) {
        R[x]->ans += R[E[x][i]]->ans;
        vector<int>& T = R[E[x][i]]->A;
        for(auto iter = T.rbegin(), jter = R[x]->A.rbegin(); iter != T.rend(); iter++, jter++)
            *jter += *iter;
    }
    for(auto &i : U) R[x]->ans = mod(R[x]->ans+i.fi-i.se-1LL, P);
    R[x]->A.push_back(1);
    //cout << x << " " << R[x]->ans << "\n " << R[x]->A << " " << U;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, r = 0; cin >> n;
    vector<vector<int>> E(n);
    vector<int> D(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x != -1) E[--x].push_back(i);
        else r = i;
    }
    dfs(r, E, D);
    vector<res*> R(n, NULL);
    solve(r, E, R);
    cout << R[r]->ans << "\n";
    return 0;
}
