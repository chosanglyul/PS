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

struct Point {
    ll x, y;
    Point(ll x, ll y) : x(x), y(y) {}
};

ostream& operator<<(ostream& out, Point a) {
    cout << '(' << a.x << ' ' << a.y << ')';
    return out;
}

int ccw(Point a, Point b, Point c) {
    ll x = (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
    return (int)(x > 0) - (int)(x < 0);
}

bool operator<(Point a, Point b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

bool operator>(Point a, Point b) {
    return b < a;
}

bool operator<=(Point a, Point b) {
    return (a < b) || (a.x == b.x && a.y == b.y);
}

bool intersect(Point p1, Point p2, Point p3, Point p4) {
    int r1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
    int r2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
    if (r1 == 0 && r2 == 0) {
        if (p1 > p2) swap(p1, p2);
        if (p3 > p4) swap(p3, p4);
        return (!(p2 < p3 || p4 < p1) ? 1 : 0);
    } else {
        return (r1 <= 0 && r2 <= 0 ? 1 : 0);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 2;
    vector<pair<Point, Point>> L;
    for(int i = 0; i < n; i++) {
        ll sx, sy, ex, ey; cin >> sx >> sy >> ex >> ey;
        Point s(sx, sy), e(ex, ey);
        L.push_back({s, e});
    }
    cout << (int)intersect(L[0].fi, L[0].se, L[1].fi, L[1].se) << "\n";
    return 0;
}