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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; return os; }
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

vector<int> I() {
    int n; cin >> n;
    vector<int> A(n), B(1, 0), C;
    for(auto &i : A) cin >> i;
    for(int i = 0; i < n; i++) B.push_back(B.back()+A[i]);
    for(int i = 0; i < n; i++)
        for(int j = i+1; j <= n; j++)
            C.push_back(B[j]-B[i]);
    sort(C.begin(), C.end());
    return C;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    vector<int> A = I();
    vector<int> B = I();
    ll cnt = 0;
    for(int i = 0; i < A.size(); i++) cnt += upper_bound(B.begin(), B.end(), t-A[i]) - lower_bound(B.begin(), B.end(), t-A[i]);
    cout << cnt << endl;
    return 0;
}