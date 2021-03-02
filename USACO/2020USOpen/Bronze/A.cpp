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
    int n; cin >> n;
    string s; cin >> s;
    int ans = INF, cnt = 0;
    vector<int> A, B;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            if(cnt == 0 && A.size()) ans = 1;
            if(A.empty()) {
                A.push_back(cnt);
                B.push_back(cnt/2);
            } else {
                A.push_back((cnt+1)/2);
                B.push_back((cnt+1)/3);
                ans = min(ans, cnt+1);
            }
            cnt = 0;
        } else cnt++;
    }
    A.push_back(cnt);
    B.push_back(cnt/2);
    sort(A.begin(), A.end(), [&](int a, int b) { return a > b; });
    sort(B.begin(), B.end(), [&](int a, int b) { return a > b; });
    if(A.size() > 1) cout << min(ans, max(A[1], B[0])) << "\n";
    else cout << n-1 << "\n";
    return 0;
}