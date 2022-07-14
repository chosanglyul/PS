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

ll solve(ll x, deque<pl>& A) {
    while(A.size() > 1 && A[0].fi*x+A[0].se >= A[1].fi*x+A[1].se) A.pop_front();
    return A[0].fi*x+A[0].se;
}

void push(pl t, deque<pl>& A) {
    //while(A.size() && A.back().fi*x+A.back().se >= t.fi*x+t.se) A.pop_back();
    while(A.size() && A.back().fi == t.fi && A.back().fi > t.se) A.pop_back();
    while(A.size() > 1) {
        pl x = A.back(), y = A[A.size()-2];
        if((x.se-y.se)*(x.fi-t.fi) > (t.se-x.se)*(y.fi-x.fi)) A.pop_back();
        else break;
    }
    A.push_back(t);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pl> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    sort(A.begin(), A.end(), greater<pl>());
    ll tmp = 0LL;
    vector<ll> D(1, 0LL);
    deque<pl> B;
    for(auto &i : A) {
        if(tmp < i.se) {
            tmp = i.se;
            push({i.fi, D.back()}, B);
            D.push_back(solve(i.se, B));
        }
    }
    cout << D.back() << "\n";
    return 0;
}