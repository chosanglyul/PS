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

struct UF {
    vector<int> P;

    int fin(int x) {
        if(x == P[x]) return x;
        return P[x] = fin(P[x]);
    }

    void mer(int x, int y) {
        x = fin(x), y = fin(y);
        if(x != y) P[x] = y;
    }

    UF(int n) {
        P.resize(n);
        for(int i = 0; i < n; i++) P[i] = i;
    }
};

int solve(vector<pll> &A) {
    UF uf(A.size());
    vector<bool> chk(A.size(), false);
    for(int i = 0; i < A.size(); i++) {
        if(chk[i]) continue;
        for(int j = i+1; j < A.size(); j++) {
            if(A[i] == A[j]) {
                chk[j] = true;
                uf.mer(i, j);
            }
        }
    }
    vector<int> cnt(A.size(), 0);
    for(int i = 0; i < A.size(); i++) cnt[uf.fin(i)]++;
    return *max_element(cnt.begin(), cnt.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll x, y; cin >> x >> y;
    int n, ans = 0; cin >> n;
    vector<pll> L, R;
    for(int i = 0; i < n; i++) {
        ll xx, yy; cin >> xx >> yy;
        if(yy >= y) continue;
        pll tmp = {(xx-x)*(xx-x), y-yy};
        ll gg = __gcd(tmp.fi, tmp.se);
        tmp.fi /= gg, tmp.se /= gg;
        if(xx > x) R.push_back(tmp);
        else if(xx < x) L.push_back(tmp);
        else ans++;
    }
    cout << max(ans, max(solve(L), solve(R))) << "\n";
    return 0;
}