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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

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
    string s; cin >> s;
    deque<int> A;
    vector<pi> B;
    for(int i = 0, j = 1; i < s.size(); i++, j++) {
        if(i+1 == s.size() || s[i] != s[i+1]) {
            A.push_back(j);
            j = 0;
        }
    }
    while(A.size() > 3) {
        if(A[1] >= A[2]) {
            B.push_back({A[0]+A[1]-A[2]+1, A[0]+A[1]+A[2]});
            A[3] += A[1]-A[2];
            A[2] = A[0];
        } else {
            B.push_back({A[0]+1, A[0]+A[1]*2});
            A[2] += A[0]-A[1];
        }
        A.pop_front();
        A.pop_front();
    }
    if(A.size() == 3) {
        B.push_back({A[0]+A[1]-A[2]+1, A[0]+A[1]+A[2]});
        A[1] -= A[2];
        A.pop_back();
    }
    B.push_back({1, A[0]+A[1]});
    cout << B.size() << "\n";
    for(auto i : B) cout << i << "\n";
    return 0;
}