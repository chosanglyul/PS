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

vector<int> getPi(string &s) {
    vector<int> pi(s.size(), 0);
    for(int i = 1, j = 0; i < s.size(); i++) {
        while(j && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) pi[i] = ++j;
    }
    return pi;
}

bool solve(string &s, string &t, vector<int> &pi) {
    for(int i = 0, j = 0; i < t.size(); i++) {
        while(j && t[i] != s[j]) j = pi[j-1];
        if(t[i] == s[j]) j++;
        if(j == s.size()) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, t; cin >> s >> t;
    vector<int> pi = getPi(t);
    if(solve(t, s, pi)) cout << 1 << "\n";
    else cout << 0 << "\n";
    return 0;
}
