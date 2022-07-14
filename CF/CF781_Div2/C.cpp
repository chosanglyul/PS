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
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> A(n+1, 0);
        A[0] = 1;
        for(int i = 0; i < n-1; i++) {
            int x; cin >> x;
            A[x]++;
        }
        vector<int> B;
        for(auto i : A) if(i) B.push_back(i);
        sort(B.begin(), B.end());
        reverse(B.begin(), B.end());
        int m = (int)B.size();
        for(int i = 0; i < m; i++) B[i] -= m-i;
        priority_queue<int> Q;
        for(auto i : B) Q.push(i);
        int cnt = 0;
        while(Q.size() && Q.top() > cnt) {
            int tmp = Q.top(); Q.pop();
            Q.push(--tmp); ++cnt;
        }
        cout << m+cnt << "\n";
    }
    return 0;
}