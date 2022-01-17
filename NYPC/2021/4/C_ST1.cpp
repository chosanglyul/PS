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

struct line { int y, s, e, c, k; };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<line> A(n); //(y, c), (s, e)
    vector<int> C;
    for(int i = 0; i < n; i++) {
        A[i].k = i;
        cin >> A[i].y >> A[i].s >> A[i].e >> A[i].c;
        C.push_back(A[i].s); C.push_back(A[i].e);
    }
    sort(C.begin(), C.end());
    C.erase(unique(C.begin(), C.end()), C.end());
    for(auto &i : A) {
        i.s = lower_bound(C.begin(), C.end(), i.s) - C.begin();
        i.e = lower_bound(C.begin(), C.end(), i.e) - C.begin(); i.e++;
    }
    sort(A.begin(), A.end(), [&](line a, line b) { return a.y < b.y; });
    vector<ll> D(n);
    for(int i = 0; i < n; i++) {
        D[i] = (ll)A[i].y*A[i].y;
        for(int j = 0; j < n-1; j++) {
            if(A[j].y >= A[i].y || A[i].e <= A[j].s || A[j].e <= A[i].s) continue;
            ll dta = A[i].y-A[j].y;
            D[i] = min(D[i], D[j]+dta*dta+A[j].c);
        }
    }
    vector<ll> E(n);
    for(int i = 0; i < n; i++) E[A[i].k] = D[i];
    for(auto i : E) cout << i << "\n";
    return 0;
}