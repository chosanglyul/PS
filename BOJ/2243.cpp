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

vector<int> seg(4040404, 0);

int query(int i, int s, int e, int k) {
    if(s+1 == e) return s;
    if(seg[i<<1] >= k) return query(i<<1, s, s+e>>1, k);
    else return query(i<<1|1, s+e>>1, e, k-seg[i<<1]);
}

void update(int i, int s, int e, int j, int x) {
    if(j < s || j >= e) return;
    if(s+1 == e) seg[i] += x;
    else {
        update(i<<1, s, s+e>>1, j, x);
        update(i<<1|1, s+e>>1, e, j, x);
        seg[i] = seg[i<<1]+seg[i<<1|1];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pii> Q;
    while(n--) {
        int x, y, z = 0; cin >> x >> y;
        if(--x) cin >> z;
        Q.push_back({x, {y, z}});
    }
    for(auto &i : Q) {
        if(i.fi == 0) {
            int tmp = query(1, 0, 1010101, i.se.fi);
            cout << tmp << "\n";
            update(1, 0, 1010101, tmp, -1);
        }
        else update(1, 0, 1010101, i.se.fi, i.se.se);
    }
    return 0;
}