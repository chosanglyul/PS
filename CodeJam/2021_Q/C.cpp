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
    int t; cin >> t;
    for(int kk = 1; kk <= t; kk++) {
        int n, c; cin >> n >> c;
        c -= n-1;
        cout << "Case #" << kk << ": ";
        if(c < 0 || c > (n-1)*n/2) {
            cout  << "IMPOSSIBLE\n";
            continue;
        }
        deque<int> A;
        for(int i = 0; i < n; i++) {
            int th = n-i;
            if(A.empty() || c == 0) A.push_front(th);
            else {
                if(c > i) {
                    c -= i;
                    reverse(A.begin(), A.end());
                    A.push_back(th);
                } else {
                    reverse(A.begin(), A.begin()+c);
                    A.insert(A.begin()+c, th);
                    c = 0;
                }
            }
        }
        for(auto i : A) cout << i << " ";
        cout << "\n";
    }
    return 0;
}