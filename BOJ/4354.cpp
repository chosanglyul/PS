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

vector<int> getpi(string& b) {
    vector<int> pi(b.size(), 0);
    for(int i = 1; i < b.size(); i++) {
        pi[i] = pi[i-1];
        while(pi[i] > 0 && b[pi[i]] != b[i]) pi[i] = pi[pi[i]-1];
        if(b[pi[i]] == b[i]) pi[i]++;
    }
    return pi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while(true) {
        string s; cin >> s;
        if(s == ".") break;
        int ans = 1, n = s.size();
        vector<int> pi = getpi(s);
        for(int i = 1; i*2 <= n; i++) {
            if(n%i) continue;
            bool can = true;
            for(int j = 2*i-1; j < n; j += i) {
                if(pi[j] == 0 || pi[j]%i) can = false;
            }
            if(can) ans = max(ans, n/i);
        }
        cout << ans << "\n";
    }
    return 0;
}