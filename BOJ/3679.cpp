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
const ll LLINF = 1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

struct Point {
    ll x, y;
    Point(ll x, ll y) : x(x), y(y) {}
};
ostream& operator<<(ostream& out, Point a) {
    cout << '(' << a.x << ' ' << a.y << ')';
    return out;
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
int ccw(Point a, Point b, Point c) {
    ll x = (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
    return (int)(x > 0) - (int)(x < 0);
}
ll dst(Point p, Point q) {
    return (p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y);
}

typedef pair<Point, int> ppi;
vector<int> sorting(vector<ppi> A) {
    swap(A[0], *min_element(A.begin(), A.end()));
    sort(A.begin()+1, A.end(), [&](ppi x, ppi y) {
        Point a = x.fi, b = y.fi, c = A[0].fi;
        ll cw = ccw(c, a, b);
        if(cw) return cw > 0;
        return dst(c, a) < dst(c, b);
    });
    int idx = (int)A.size()-2;
    while(idx >= 0 && ccw(A[0].fi, A[idx].fi, A[idx+1].fi) == 0) idx--;
    reverse(A.begin()+(++idx), A.end());
    vector<int> R;
    for(auto &i : A) R.push_back(i.se);
    return R;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    while(n--) {
        int m; cin >> m;
        vector<ppi> A;
        for(int i = 0; i < m; i++) {
            int x, y; cin >> x >> y;
            A.push_back({Point(x, y), i});
        }
        cout << sorting(A);
    }
    return 0;
}