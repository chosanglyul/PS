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

vector<int> can(vector<deque<char>>& D, vector<bool>& chk) {
    vector<int> A;
    for(int i = 0; i < D.size(); i++)
        if(D[i].empty()) A.push_back(i);
    reverse(A.begin(), A.end());
    for(auto i : A) {
        D.erase(D.begin()+i);
        chk.erase(chk.begin()+i);
    }
    vector<int> B = {0};
    for(auto &i : D) B.push_back(B.back()+i.size());
    return B;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    string s; cin >> s;
    int n = s.size(), q; cin >> q;
    int sq = sqrt(n)+1;
    vector<deque<char>> D(sq);
    vector<bool> chk(sq, false);
    for(int i = 0; i < sq; i++)
        for(int j = i*sq; j < min(n, (i+1)*sq); j++)
            D[i].push_back(s[j]);
    vector<int> A = can(D, chk);
    while(q--) {
        if(A.size() != D.size()+1) exit(1);
        for(auto &i : D) if(i.empty()) exit(1);
        int x, y; cin >> x >> y; --x, --y;
        int xx = upper_bound(A.begin(), A.end(), x) - A.begin() - 1;
        int yy = upper_bound(A.begin(), A.end(), y) - A.begin() - 1;
        if(xx+1 < yy) {
            for(int i = xx+1; i < yy; i++) chk[i] = !chk[i];
            reverse(D.begin()+xx+1, D.begin()+yy);
            reverse(chk.begin()+xx+1, chk.begin()+yy);
        }
        x -= A[xx], y -= A[yy];
        if(chk[xx]) reverse(D[xx].begin(), D[xx].end()), chk[xx] = false;
        if(chk[yy]) reverse(D[yy].begin(), D[yy].end()), chk[yy] = false;
        if(xx == yy) {
            reverse(D[xx].begin()+x, D[xx].begin()+y+1);
        } else {
            vector<int> P, Q;
            int p = D[xx].size(), q = D[yy].size();
            for(int i = x; i < p; i++) {
                P.push_back(D[xx].back());
                D[xx].pop_back();
            }
            for(int i = 0; i <= y; i++) {
                Q.push_back(D[yy].front());
                D[yy].pop_front();
            }
            while(P.size()) {
                D[yy].push_front(P.back());
                P.pop_back();
            }
            while(Q.size()) {
                D[xx].push_back(Q.back());
                Q.pop_back();
            }
        }
        A = can(D, chk);
    }
    for(int i = 0; i < D.size(); i++) {
        if(chk[i]) reverse(D[i].begin(), D[i].end());
        for(auto j : D[i]) cout << j;
    }
    cout << "\n";
    return 0;
}