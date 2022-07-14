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

class solve {
    private:
    bool rev;
    ll R = -1;
    vector<ll> P, Q;

    public:
    solve(string s, bool rev) {
        this->rev = rev;
        if(rev) reverse(s.begin(), s.end());
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == 'R') {
                this->R = i;
                break;
            } else if(s[i] == 'P') P.push_back(i);
        }
        Q.push_back(0LL);
        for(auto i : P) Q.push_back(Q.back()+i);
    }
    pl query(ll x) {
        ll n = (ll)P.size();
        ll l = lower_bound(P.begin(), P.end(), x) - P.begin();
        ll r = n-l;
        ll cntR = max(0LL, (rev ? l-r : l-r+1LL));
        ll cntP = (rev ? l : l+1) - cntR;
        ll ans = cntR*(R-x) + (Q[l+cntP] - Q[l] - cntP*x) + (l*x - Q[l]);
        ll cnt = (rev ? l+min(l, r) : l+min(r, l+1));
        return {cnt, 2*ans+x+1};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<ll> R;
    vector<vector<ll>> P(1);
    for(int i = 0; i < n; i++) {
        if(s[i] == 'R') {
            R.push_back(i);
            P.push_back(vector<ll>());
        } else if(s[i] == 'P') P.back().push_back(i);
    }
    solve LQ(s, false), RQ(s, true);
    vector<ll> Q(1, 0LL);
    for(auto i : P[0]) Q.push_back(Q.back()+i);
    while(q--) {
        ll x; cin >> x; --x;
        if(R.empty()) {
            ll l = lower_bound(P[0].begin(), P[0].end(), x) - P[0].begin();
            ll r = (ll)P[0].size() - l;
            ll cntL = min(l, r), cntR = min(r, l+1);
            ll ans = ((Q[l+cntR] - Q[l]) - cntR*x) + (cntL*x - (Q[l] - Q[l-cntL]));
            ans = ans*2LL + (l < r ? x+1 : n-x);
            cout << cntL+cntR << " " << ans << "\n";
        } else {
            int idx = lower_bound(R.begin(), R.end(), x) - R.begin();
            if(idx == 0) {
                cout << LQ.query(x) << "\n";
            } else if(idx == R.size()) {
                cout << RQ.query(n-1-x) << "\n";
            } else cout << P[idx].size() << " -1\n";
        }
    }
    return 0;
}