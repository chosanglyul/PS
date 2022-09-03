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

/* https://github.com/justiceHui/AlgorithmImplement/blob/master/Math/ExtendGCD.cpp */
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
    cout.tie(nullptr);
    int t; cin >> t;
    vector<ll> F(1, 1LL), I;
    for(int i = 1; i <= 505050; i++) F.push_back((F.back()*i)%P);
    I.push_back(inv(F.back(), P));
    for(int i = 505050; i > 0; i--) I.push_back((I.back()*i)%P);
    reverse(I.begin(), I.end());
    for(int _t = 0; _t < t; _t++) {
        int n, k; cin >> n >> k;
        vector<ll> A(n), B(1, 0LL);
        for(auto &i : A) {
            cin >> i;
            B.push_back(B.back()+i);
        }
        ll su = B.back();
        cout << "Case #" << _t+1 << endl;
        if(su%k) {
            cout << 0 << endl;
        } else if(su == 0LL) {
            int cnt = 0;
            for(int i = 1; i <= n; i++) if(B[i] == 0LL) cnt++;
            if(k > cnt) cout << 0 << endl;
            else cout << (((F[cnt-1]*I[k-1])%P)*I[cnt-k])%P << endl;
        } else {
            su /= k;
            vector<ll> C(k, 0LL);
            C[0] = 1LL;
            for(int i = 1; i <= n; i++) {
                if(B[i]%su == 0LL) {
                    ll tmp = B[i]/su;
                    if(0LL < tmp && tmp < k) C[tmp] = (C[tmp]+C[tmp-1])%P;
                }
            }
            cout << C.back() << endl;
        }
    }
    return 0;
}