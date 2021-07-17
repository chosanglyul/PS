#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const double eps = 1e-7;

double solve(double c, double m, double p, double v, int k) {
    if(c < eps && m < eps) return (double)k;
    if(c < eps) {
        if(m < v) return p*k+m*(k+1);
        else return p*k+m*solve(0.0, m-v, p+v, v, k+1);
    }
    if(m < eps) {
        if(c < v) return p*k+c*(k+1);
        else return p*k+c*solve(c-v, 0.0, p+v, v, k+1);
    }
    double ret = p*k;
    if(c < v) ret += c*solve(0.0, m+c/2, p+c/2, v, k+1);
    else ret += c*solve(c-v, m+v/2, p+v/2, v, k+1);
    if(m < v) ret += m*solve(c+m/2, 0.0, p+m/2, v, k+1);
    else ret += m*solve(c+v/2, m-v, p+v/2, v, k+1);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        double c, m, p, v; cin >> c >> m >> p >> v;
        cout << fixed << setprecision(10) << solve(c, m, p, v, 1) << "\n";
    }
    return 0;
}