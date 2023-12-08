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

struct head {
    int par, siz;
    map<int, ll> M;
    head() {
        par = 0, siz = 0;
        M.clear();
    }
};

class UF {
    private:
    vector<head> par;

    public:
    UF(vector<int> &A) {
        int n = A.size();
        par.resize(n);
        for(int i = 0; i < n; i++) {
            par[i].par = i;
            par[i].siz = 1;
            par[i].M.insert({A[i], 1});
        }
    }

    int fin(int i) {
        if(par[i].par == i) return i;
        return par[i].par = fin(par[i].par);
    }

    void mer(int i, int j, vector<ll> &ans, ll x) {
        i = fin(i), j = fin(j);
        if(i == j) return;
        if(par[i].siz < par[j].siz) swap(i, j);
        par[j].par = i;
        for(auto iter = par[j].M.begin(); iter != par[j].M.end(); iter++) {
            auto jter = par[i].M.find(iter->fi);
            if(jter == par[i].M.end()) continue;
            ans[iter->fi] += (iter->se)*(jter->se)*x;
        }
        for(auto iter = par[j].M.begin(); iter != par[j].M.end(); iter++) {
            par[i].siz += (iter->se);
            auto jter = par[i].M.find(iter->fi);
            if(jter == par[i].M.end()) par[i].M.insert(*iter);
            else par[i].M[iter->fi] += (iter->se);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, m; cin >> n >> k >> m;
    vector<int> A(n);
    for(auto &i : A) { cin >> i; i--; }
    UF uf(A);
    vector<piii> E(m);
    for(auto &i : E) {
        cin >> i.se.fi >> i.se.se >> i.fi;
        i.se.fi--, i.se.se--;
    }
    sort(E.begin(), E.end(), greater<piii>());

    vector<ll> ans(k, 0LL);
    for(auto &i : E) {
        uf.mer(i.se.fi, i.se.se, ans, i.fi);
    }
    for(auto &i : ans) cout << i << "\n";
    return 0;
}