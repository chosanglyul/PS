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

void out(int x, vector<int> A) {
    if(x == 0) return;
    out(x-1, A);
    cout << A[x-1] << "\n";
    out(x-1, A);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A;
    vector<bool> chk(1<<20, false); chk[0] = true;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        vector<bool> t(chk);
        bool can = false;
        for(int j = 0; j < chk.size(); j++)
            if(chk[j] && !chk[j^x])
                can = t[j^x] = true;
        if(can) {
            A.push_back(i+1);
            chk = t;
        }
    }
    cout << ((1<<((int)A.size()))-1) << "\n";
    out(A.size(), A);
    return 0;
}