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
    int t, n, q; cin >> t >> n >> q;
    while(t--) {
        deque<int> A;
        A.push_back(1);
        A.push_back(2);
        for(int i = 3; i <= n; i++) {
            cout << A.front() << " " << A.back() << " " << i << "\n";
            fflush(stdout);
            int x; cin >> x;
            if(x == A.front()) A.push_front(i);
            else if(x == A.back()) A.push_back(i);
            else {
                int l = 0, r = A.size(); r--;
                while(l+1 < r) {
                    int mi = l+r>>1;
                    cout << A[l] << " " << A[mi] << " " << i << "\n";
                    fflush(stdout);
                    cin >> x;
                    if(x == i) r = mi;
                    else l = mi;
                }
                A.insert(A.begin()+r, i);
            }
        }
        for(auto i : A) cout << i << " ";
        cout << "\n";
        fflush(stdout);
        int ver; cin >> ver;
    }
    return 0;
}