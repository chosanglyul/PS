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
const ll LLINF = 1e18+1;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<pi> A(n);
    map<int, int> B;
    for(auto &i : A) cin >> i.se >> i.fi;
    for(int i = 0; i < k; i++) {
        int x; cin >> x;
        if(B.find(x) == B.end()) B.insert({x, 0});
        B[x]++;
    }
    std::sort(A.begin(), A.end(), greater<pi>());
    ll ans = 0LL;
    for(auto &i : A) {
        if(B.empty()) break;
        auto iter = B.lower_bound(i.se);
        if(iter == B.end()) continue;
        iter->se--; ans += i.fi;
        if(iter->se == 0) B.erase(iter);
    }
    cout << ans << "\n";
    return 0;
}