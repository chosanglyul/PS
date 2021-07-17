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

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n; cin >> n;
    vector<pi> A(n);
    for(auto &i : A) {
        cin >> i.fi >> i.se;
        if(i.fi > i.se) swap(i.fi, i.se);
    }
    int d; cin >> d;
    vector<pi> S, E;
    for(int i = 0; i < n; i++) {
        if(A[i].se - A[i].fi > d) continue;
        S.push_back({A[i].fi, i});
        E.push_back({A[i].se, i});
    }
    sort(S.begin(), S.end());
    sort(E.begin(), E.end());
    set<int> R;
    int ans = 0;
    //cout << S << E;
    for(int i = 0, j = 0, k = 0; i < S.size(); i++) {
        //R.insert(S[i].se);
        while(j < S.size() && S[j].fi < S[i].fi)
            R.erase(S[j++].se);
        while(k < E.size() && E[k].fi <= S[i].fi+d) {
            if(A[E[k].se].fi >= S[i].fi)
                R.insert(E[k].se);
            k++;
        }
        //cout << i << " " << j << " " << R.size() << "\n";
        //for(auto &w : R) cout << w << " ";
        //cout << "\n";
        ans = max(ans, (int)R.size());
    }
    cout << ans << "\n";
    return 0;
}