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
Point operator-(Point a, Point b) {
	return {a.x - b.x, a.y - b.y};
}
ll operator/(Point a, Point b){
	return a.x * b.y - a.y * b.x;
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

ll dst(Point p, Point q) {
    return (p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y);
}

vector<Point> convex_hull(vector<Point> A) {
    assert(A.size() >= 2);
    vector<Point> hull;
    swap(A[0], *min_element(A.begin(), A.end()));
    sort(A.begin()+1, A.end(), [&](Point a, Point b) {
        ll cw = ccw(A[0], a, b);
        if(cw) return cw > 0;
        return dst(A[0], a) < dst(A[0], b);
    });
    for(auto &i : A) {
        while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), i) <= 0) hull.pop_back();
        hull.push_back(i);
    }
    return hull;
}

pii rotating_calipers(vector<Point> A) {
	// A[0] should be mininum element, A should be a convex polygon and sorted in ccw
	int n = A.size(); A.push_back(A[0]);
    pii ret = {0, 0};
    int l = 0, r = 0;
    while(l < n) {
        // A[l], A[r] are antipodal points
        // your code here
        if(dst(A[l], A[r]) > dst(A[ret.fi], A[ret.se])) ret = {l, r};
        if(r+1 == l || (A[l+1]-A[l])/(A[r+1]-A[r]) <= 0) l++;
        else r++;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<Point> A(n, {0, 0});
        for(auto &i : A) cin >> i.x >> i.y;
        vector<Point> hull = convex_hull(A);
        pii ans = rotating_calipers(hull);
        cout << hull[ans.fi].x << " " << hull[ans.fi].y <<
                " " << hull[ans.se].x << " " << hull[ans.se].y << "\n";
    }
    return 0;
}