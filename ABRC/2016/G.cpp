#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

const int MOD = 1e9 + 7;

struct Matrix {
    ll a, b, c, d;
};

Matrix operator*(const Matrix& l, const Matrix& r) {
    Matrix ret;
    ret.a = (l.a * r.a + l.b * r.c) % MOD;
    ret.b = (l.a * r.b + l.b * r.d) % MOD;
    ret.c = (l.c * r.a + l.d * r.c) % MOD;
    ret.d = (l.c * r.b + l.d * r.d) % MOD;
    return ret;
}

Matrix operator+(const Matrix& l, const Matrix& r) {
    Matrix ret;
    ret.a = l.a + r.a;
    ret.b = l.b + r.b;
    ret.c = l.c + r.c;
    ret.d = l.d + r.d;
    if (ret.a >= MOD) ret.a -= MOD;
    if (ret.b >= MOD) ret.b -= MOD;
    if (ret.c >= MOD) ret.c -= MOD;
    if (ret.d >= MOD) ret.d -= MOD;
    return ret;
}

Matrix power(ll p) {
    Matrix ret = { 1, 0, 0, 1 };
    Matrix a = { 1, 1, 1, 0 };
    while (p > 0) {
        if (p & 1) ret = ret * a;
        a = a * a;
        p /= 2;
    }
    return ret;
}

ostream& operator<<(ostream& out, const Matrix& m) {
    out << '(' << m.a << ' ' << m.b << ' ' << m.c << ' ' << m.d << ')';
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;
    for (int ic=1; ic<=cases; ++ic) {
        ll l, r, k;
        cin >> l >> r >> k;
        ll a = (l+k-1)/k, b = r/k;
        
        Matrix ans = {0,0,0,0};
        Matrix accum = { 1, 0, 0, 1 };
        ll len = b-a+1;
        for (int i=0; i<60; ++i) {
            if (len & (1ll << i)) {
                ans = ans + (accum * power(a*k));
                a += (1ll << i);
            }
            accum = accum + (accum * power((1ll << i)*k));
            //cout << i << endl;
            //cout << ans << endl << accum << endl;
        }
        cout << "Case " << ic << ": " << (ans.a + ans.b) % MOD << '\n';
    }

    return 0;
}