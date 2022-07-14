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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<int> A(n), chk(n, 0);
        for(auto &i : A) {
            cin >> i;
            if(i < n) chk[i]++;
        }
        vector<int> B(A);
        sort(A.begin(), A.end());
        reverse(A.begin(), A.end());
        int mex = 0;
        while(mex < n && chk[mex] > 0) mex++;
        for(int i = 0, j = 0; i < n && j < k; i++) {
            if(A[i] > mex || chk[A[i]] > 1) {
                j++;
                if(A[i] < n) chk[A[i]]--;
                A[i] = mex; chk[mex]++;
                while(mex < n && chk[mex] > 0) mex++;
            }
        }
        sort(B.begin(), B.end());
        reverse(B.begin(), B.end());
        vector<pi> C;
        vector<int> D;
        for(int i = 0; i < n && B[i] > mex; i++) {
            D.push_back(B[i]);
            if(C.empty() || C.back().se != B[i]) C.push_back({1, B[i]});
            else C.back().fi++;
        }
        sort(C.begin(), C.end());
        int cnt = 0;
        for(int i = 0, j = 0; i < C.size() && j < k; i++) {
            j += C[i].fi;
            if(j <= k) cnt++;
        }
        sort(D.begin(), D.end());
        D.erase(unique(D.begin(), D.end()), D.end());
        cout << (int)D.size() - cnt << "\n";
    }
    return 0;
}