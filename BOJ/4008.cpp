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

double cross(pl a, pl b) { return (double)(a.se-b.se)/(double)(b.fi-a.fi); }

void insert(vector<pl>& A, pl x) {
    while(A.size() && A.back().fi == x.fi && A.back().se <= x.se) A.pop_back();
    while(A.size() >= 2 && cross(x, A.back()) <= cross(A.back(), A[A.size()-2])) A.pop_back();
    A.push_back(x);
}

ll query(vector<pl>& A, ll x) {
    int l = 0, r = A.size();
    while(l+1 < r) {
        int mi = l+r>>1;
        if(cross(A[mi-1], A[mi]) >= x) r = mi;
        else l = mi;
    }
    return A[l].fi*x+A[l].se;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    ll a, b, c; cin >> a >> b >> c;
    vector<ll> A(n), B(n), C(n);
    vector<pl> D;
    for(auto &i : A) cin >> i;
    B[0] = A[0];
    for(int i = 1; i < n; i++) B[i] = B[i-1]+A[i];
    insert(D, {0, 0});
    for(int i = 0; i < n; i++) {
        C[i] = a*B[i]*B[i]+b*B[i]+c+query(D, B[i]);
        insert(D, {-2*a*B[i], a*B[i]*B[i]-b*B[i]+C[i]});
    }
    cout << C.back() << "\n";
    return 0;
}