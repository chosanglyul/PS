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

int query(int l, int r) {
    if(l >= r-1) exit(1);
    cout << "? " << l+1 << " " << r << "\n";
    fflush(stdout);
    int x; cin >> x;
    return --x;
}

int main() {
    int n; cin >> n;
    int l = 0, r = n;
    while(l+1 < r) {
        int x = query(l, r);
        if(r-l == 2) {
            if(x == l) l++;
            else r--;
        } else if(r-l == 3) {
            if(x == l) l++;
            else if(x == l+2) r--;
            else {
                int y = query(l, r-1);
                if(x != y) l += 2;
                else r -= 2;
            }
        } else {
            int mi = (l+r)>>1;
            if(x < mi) {
                int y = query(l, mi);
                if(x == y) r = mi;
                else l = mi;
            } else {
                int y = query(mi, r);
                if(x == y) l = mi;
                else r = mi;
            }
        }
    }
    cout << "! " << l+1 << "\n";
    fflush(stdout);
    return 0;
}