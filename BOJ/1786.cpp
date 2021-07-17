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

vector<int> getPi(string& s) {
    vector<int> ans(s.size(), 0);
    for(int i = 1, j = 0; i < s.size(); i++) {
        while(j > 0 && s[j] != s[i]) j = ans[j-1];
        if(s[j] == s[i]) ans[i] = ++j;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string t, p;
    getline(cin, t);
    getline(cin, p);
    vector<int> pi = getPi(p), ans;
    for(int i = 0, j = 0; i < t.size(); i++) {
        while(j > 0 && p[j] != t[i]) j = pi[j-1];
        if(t[i] == p[j]) j++;
        if(j == p.size()) {
            ans.push_back(i-p.size()+2);
            j = pi[j-1];
        }
    }
    cout << ans.size() << "\n";
    for(auto i : ans) cout << i << "\n";
    return 0;
}