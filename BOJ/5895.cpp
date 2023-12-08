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

pii gen(int y, pii x) {
    if(y == 0) return x;
    if(y == 1) return {x.se, -x.fi};
    if(y == 2) return {-x.fi, -x.se};
    if(y == 3) return {-x.se, x.fi};
    assert(false);
    return {0, 0};
}

pii solve(char c, pii x) {
    if(c == 'L') return gen(3, x);
    else if(c == 'R') return gen(1, x);
    else return {x.fi, x.se+1};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    vector<piii> A = {{0, {0, 0}}};
    const vector<pii> B = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'L') A.push_back({(A.back().fi+3)%4, A.back().se});
        else if(s[i] == 'R') A.push_back({(A.back().fi+1)%4, A.back().se});
        else {
            int idx = A.back().fi;
            A.push_back({idx, {B[idx].fi+A.back().se.fi, B[idx].se+A.back().se.se}});
        }
    }
    // cout << A;
    vector<pii> C = {{0, 0}};
    for(int i = s.size()-1; i >= 0; i--) C.push_back(solve(s[i], C.back()));
    // cout << C;
    const vector<char> D = {'L', 'R', 'F'};
    vector<pii> E;
    for(int i = 0; i < s.size(); i++) {
        piii x = A[i]; pii y = C[s.size()-i-1];
        for(auto c : D) {
            if(s[i] == c) continue;
            pii z = gen(x.fi, solve(c, y));
            z.fi += x.se.fi, z.se += x.se.se;
            E.push_back(z);
            // cout << c << " " << z << "\n";
        }
    }
    sort(E.begin(), E.end());
    E.erase(unique(E.begin(), E.end()), E.end());
    // cout << E;
    cout << E.size() << "\n";
    return 0;
}
