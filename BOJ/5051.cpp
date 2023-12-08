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
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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

// multiply: input format - [x^0 coeff, x^1 coeff, ...], [same], [anything]
typedef complex<double> base;
const double PI = acos(-1);
void fft(vector<base>& a, bool inv) {
    int n = a.size();
    for (int dest=1, src=0; dest<n; ++dest) {
        int bit = n / 2;
        while (src >= bit) {
            src -= bit;
            bit /= 2;
        }
        src += bit;
        if (dest < src) { swap(a[dest], a[src]); }
    }
    for (int len=2; len <= n; len *= 2) {
        double ang = 2 * PI / len * (inv ? -1 : 1);
        base unity(cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            base w(1, 0);
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= unity;
            }
        }
    }
    if (inv) {
        for (int i=0; i<n; ++i) { a[i] /= n; }
    }
}

void multiply(const vector<int>& a, const vector<int>& b, vector<int>& result) {
    int n = 2;
    while (n < a.size() + b.size()) { n *= 2; }

    vector<base> p(a.begin(), a.end());
    p.resize(n);
    for (int i=0; i<b.size(); ++i) { p[i] += base(0, b[i]); }
    fft(p, false);

    result.resize(n);
    for (int i=0; i<=n/2; ++i) {
        base u = p[i], v = p[(n-i) % n];
        p[i] = (u * u - conj(v) * conj(v)) * base(0, -0.25);
        p[(n-i) % n] = (v * v - conj(u) * conj(u)) * base(0, -0.25);
    }
    fft(p, true);
    for (int i=0; i<n; ++i) { result[i] = (int)round(p[i].real()); }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n, 0);
    for(int i = 1; i < n; i++) A[((ll)i*i)%n]++;
    vector<int> B;
    multiply(A, A, B);
    ll ans = 0LL;
    for(int i = 0; i < B.size(); i++) ans += (ll)A[i%n]*B[i];
    vector<int> C(n, 0);
    for(int i = 0; i < n; i++) C[(i*2)%n] += A[i];
    for(int i = 0; i < n; i++) ans += (ll)A[i]*C[i];
    cout << ans/2 << "\n";
    return 0;
}
