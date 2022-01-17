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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, q; cin >> n >> k >> q;
    vector<vector<int>> A(k), B;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        A[--y].push_back(x);
    }
    for(auto &i : A) sort(i.begin(), i.end());
    vector<int> C(q);
    for(auto &i : C) cin >> i;
    vector<int> D(C);
    sort(D.begin(), D.end());
    D.erase(unique(D.begin(), D.end()), D.end());
    B.resize(D.size());
    for(int i = 0; i < q; i++) {
        int idx = lower_bound(D.begin(), D.end(), C[i])-D.begin();
        B[idx].push_back(i);
    }
    vector<pii> E;
    for(int i = 0; i < D.size(); i++) E.push_back({D[i], {0, i}}); //{coor, {iden, val}}
    for(auto &i : A) {
        for(int j = 0; j < i.size(); j++) E.push_back({i[j], {1, 2}});
        for(int j = 0; j+1 < i.size(); j++) {
            E.push_back({(i[j]+i[j+1])/2, {1, -1}});
            E.push_back({(i[j]+i[j+1]+1)/2, {1, -1}});
        }
    }
    sort(E.begin(), E.end());
    ll x = -(ll)INF, y = -(ll)k, z = 0LL; //x coor. y delta. z value.
    for(auto &i : A) z += (ll)(i[0]-x);
    vector<ll> F(q);
    cout << E;
    for(int i = 0; i < E.size(); i++) {
        z += y*(E[i].fi-x);
        x = E[i].fi;
        if(E[i].se.fi) y += E[i].se.se;
        else for(auto j : B[E[i].se.se]) F[j] = z;
        cout << x << " " << y << " " << z << "\n";
    }
    cout << D << " ";
    cout << B;
    for(auto i : F) cout << i << "\n";
    return 0;
}