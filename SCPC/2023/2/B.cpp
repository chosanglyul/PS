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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

/* https://github.com/justiceHui/AlgorithmImplement/blob/master/Math/ExtendGCD.cpp */
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
    cout.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        cout << "Case #" << _t+1 << endl;
        int n; cin >> n;
        string s; cin >> s;
        vector<int> dp(n, 0), L(n, -1);
        ll ans = 0LL;
        for(int i = n-2; i >= 0; i--) {
            if(s[i] == '}' || s[i] == ')') {
                dp[i] = 0, L[i] = -1;
            } else {
                if((s[i] == '(' && s[i+1] == '}') || (s[i] == '{' && s[i+1] == ')')) {
                    dp[i] = 0, L[i] = -1;
                } else if((s[i] == '(' && s[i+1] == ')') || (s[i] == '{' && s[i+1] == '}')) {
                    dp[i] = 1, L[i] = i+1;
                    if(i+2 < n && L[i+2] >= 0) dp[i] += dp[i+2], L[i] = L[i+2];
                } else {
                    int idx = L[i+1]+1;
                    if(L[i+1] < 0 || idx >= n || (s[i] == '(' && s[idx] != ')') || (s[i] == '{' && s[idx] != '}')) {
                        dp[i] = 0, L[i] = -1;
                    } else {
                        dp[i] = 1, L[i] = idx;
                        if(idx+1 < n && L[idx+1] >= 0) dp[i] += dp[idx+1], L[i] = L[idx+1];
                    }
                }
            }
            ans += dp[i];
        }
        cout << ans;
        cout << endl;
    }
    return 0;
}
