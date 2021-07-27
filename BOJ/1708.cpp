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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

ll crs(pl a, pl b) { return a.fi*b.se-a.se*b.fi; }
ll ccw(pl a, pl b, pl c) { return crs(a, b)+crs(b, c)+crs(c, a); }
ll dst(pl a, pl b) { return (a.fi-b.fi)*(a.fi-b.fi)+(a.se-b.se)*(a.se-b.se); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pl> A(n), hull;
    for(auto &i : A) cin >> i.fi >> i.se;
    swap(A[0], *min_element(A.begin(), A.end()));
    sort(A.begin()+1, A.end(), [&](pi a, pi b) {
        ll cw = ccw(A[0], a, b);
        if(cw) return cw > 0;
        return dst(A[0], a) < dst(A[0], b);
    });
    for(auto &i : A) {
        while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), i) <= 0) hull.pop_back();
        hull.push_back(i);
    }
    cout << hull.size() << "\n";
    return 0;
}