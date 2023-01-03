#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 998244353;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    const int MAX = 202020;
    int n, x, y; cin >> n >> x >> y;
    vector<int> A(n), C(MAX, 0);
    vector<vector<int>> B(MAX/x+1, vector<int>(x, 0));
    for(auto &i : A) {
        cin >> i;
        B[i/x][i%x]++;
        C[i/x]++;
    }
 
    ll ans = 0LL;
    for(int i = 0; i < B.size(); i++) {
        for(int j = 0; j < x; j++) {
            int cnt = 0;
            if(i) cnt += B[i-1][j];
            if(j) cnt += B[i][j-1];
            if(i && j) cnt -= B[i-1][j-1];
            ans = (ans+(ll)B[i][j]*cnt)%P;
            B[i][j] += cnt;
        }
    }
    ll tmp = 0LL, su = 0LL;
    reverse(C.begin(), C.end());
    for(int i = 0; i < MAX; i++) {
        ans = (ans+tmp*C[i])%P;
        su = (su+C[i])%P;
        tmp = (tmp+su)%P;
    }
    cout << (ans*y)%P << " ";
 
    ans = 0LL;
    for(int i = 1; i < n; i++)
        if(A[i] > A[0])
            ans += (A[i]-A[0])/x+1LL;
    cout << (ans*y)%P << "\n";
    return 0;
}
