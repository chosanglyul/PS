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

class SALCP {
    private:
    int n;
    string s;
    vector<int> A, B, C;

    public:
    SALCP(string &s) {
        this->s = s;
        n = s.size();
    }

    vector<int> sa() {
        A.clear(); B.clear();
        for(int i = 0; i < n; i++) A.push_back(i);
        for(auto i : s) B.push_back(i-'a');
        for(int d = 1; ; d <<= 1) {
            auto cmp = [&](int a, int b) {
                if(B[a] != B[b]) return B[a] < B[b];
                a += d, b += d;
                return (a < n && b < n) ? (B[a] < B[b]) : (a > b);
            };
            sort(A.begin(), A.end(), cmp);
            vector<int> T(n, 0);
            for(int i = 1; i < n; i++) T[i] = T[i-1]+cmp(A[i-1], A[i]);
            for(int i = 0; i < n; i++) B[A[i]] = T[i];
            if(T.back() == n-1) break;
        }
        return A;
    }

    vector<int> lcp() {
        C.resize(n-1);
        for(int i = 0, j = 0; i < n; i++, j = max(j-1, 0)) {
            if(B[i] == n-1) continue;
            while(s[i+j] == s[A[B[i]+1]+j]) j++;
            C[B[i]] = j;
        }
        return C;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    SALCP salcp(s);
    vector<int> sa = salcp.sa();
    for(auto &i : sa) i++;
    vector<int> lcp = salcp.lcp();
    cout << sa << "x " << lcp;
    return 0;
}
