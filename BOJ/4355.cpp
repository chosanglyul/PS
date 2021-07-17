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
    int n;
    while(true) {
        cin >> n;
        if(n == 0) break;
        if(n == 1) {
            cout << 1 << "\n";
            continue;
        }
        vector<pi> A;
        for(int i = 2; i*i <= n; i++) {
            if(n%i == 0) {
                A.push_back({i, 0});
                while(n%i == 0) {
                    A.back().se++;
                    n /= i;
                }
            }
        }
        if(n > 1) A.push_back({n, 1});
        int ans = 1;
        for(auto &i : A) {
            int tmp = 1;
            for(int j = 0; j < i.se-1; j++) tmp *= i.fi;
            ans *= (i.fi-1)*tmp;
        }
        cout << ans << "\n";
    }
    return 0;
}