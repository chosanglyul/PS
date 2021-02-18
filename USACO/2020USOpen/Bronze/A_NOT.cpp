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
    string s; cin >> s; s += "1";
    vector<int> A;
    for(int lst = -1, i = 0; i < s.size(); i++) {
        if(s[i] == '1') {
            A.push_back(i-lst-1);
            lst = i;
        }
    }
    sort(A.begin(), A.end(), greater<int>());
    //cout << A;
    if(A[0] <= 2) cout << 1 << "\n";
    else if(A[1] == 0) cout << (A[0]-2)/3+1 << "\n";
    else cout << max((A[0]-2)/3, (A[1]-1)/2)+1 << "\n";
    return 0;
}