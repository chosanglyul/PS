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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pi> A(n);
    vector<int> B;
    for(auto &i : A) {
        cin >> i.fi >> i.se;
        B.push_back(i.fi);
        B.push_back(i.se);
    }
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());
    vector<vector<int>> C(B.size()), D(B.size());
    for(int i = 0; i < n; i++) {
        A[i].fi = lower_bound(B.begin(), B.end(), A[i].fi)-B.begin();
        A[i].se = lower_bound(B.begin(), B.end(), A[i].se)-B.begin();
        C[A[i].fi].push_back(i);
        D[A[i].se].push_back(i);
    }
    int maxt = 0, ma = 0, cnt = 0;
    for(int i = 0; i < B.size(); i++) {
        cnt += C[i].size();
        if(ma < cnt) {
            ma = cnt;
            maxt = i;
        }
        cnt -= D[i].size();
    }
    cout << ma << "\n";
    for(int i = 0; i < A.size(); i++) {
        if(maxt >= A[i].fi && maxt <= A[i].se)
            cout << i+1 << " ";
    }
    return 0;
}