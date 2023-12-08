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

vector<int> Z(string &s) {
    vector<int> ret(s.size(), 0); ret[0] = s.size();
    for(int i = 1, l = 0, r = 1; i < s.size(); i++) {
        ret[i] = max(0, min(ret[i-l], r-i));
        while(ret[i]+i < s.size() && s[i+ret[i]] == s[ret[i]]) ret[i]++;
        if(i+ret[i] > r) r = i+ret[i], l = i;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    vector<int> z = Z(s);
    vector<pii> ans;
    vector<int> tmp(s.size()+1, 0);
    for(int i = 0; i < s.size(); i++) {
        tmp[z[i]]++;
        if(i+z[i] == s.size())
            ans.push_back({z[i], 0});
    }
    for(int i = s.size(); i >= 1; i--)
        tmp[i-1] += tmp[i];
    reverse(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(auto &i : ans) {
        i.se = tmp[i.fi];
        cout << i << "\n";
    }
    return 0;
}
