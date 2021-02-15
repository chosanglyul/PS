#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
typedef vector<bitset<60>> vb;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = 1e18+1;

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

ll vtoll(vector<int> & T) {
    ll tmp = 1LL, res = 0LL;
    for(int i = 0; i < T.size(); i++, tmp = (tmp*2)%P)
        res = (res+tmp*T[i])%P;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vb A(n); vector<ll> I;
        vector<int> B(60, 0);
        for(auto &bit : A) {
            ll x; cin >> x;
            I.push_back(x%P);
            for(int i = 0; i < 60; i++, x >>= 1) {
                bit.set(i, x&1LL);
                B[i] += x&1LL;
            }
        }
        ll res = 0LL;
        for(int i = 0; i < n; i++) {
            ll or_ = (I[i]*n)%P, and_ = 0LL;
            vector<int> C(B), D(B);
            for(int j = 0; j < 60; j++) {
                if(A[i][j]) C[j] = 0;
                else D[j] = 0;
            }
            or_ = (or_+vtoll(C))%P;
            and_ = vtoll(D);
            res = (res+(or_*and_)%P)%P;
        }
        cout << res << "\n";
    }
    return 0;
}