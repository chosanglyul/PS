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
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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

void add_query(int x, int i, int sq, int j, vector<int> &dif, vector<int> &A, vector<int> &B) {
    if(dif[x] == -1) {
        dif[x] = 0;
    } else {
        A[dif[x]]--; B[dif[x]/sq]--;
        dif[x] += abs(i-j);
    }
    A[dif[x]]++; B[dif[x]/sq]++;
}
void sub_query(int x, int i, int sq, int j, vector<int> &dif, vector<int> &A, vector<int> &B) {
    A[dif[x]]--; B[dif[x]/sq]--;
    if(dif[x] == 0) {
        dif[x] = -1;
    } else {
        dif[x] -= abs(i-j);
        A[dif[x]]++; B[dif[x]/sq]++;
    }
}
int find_query(int n, int sq, vector<int> &A, vector<int> &B) {
    for(int i = n/sq; i >= 0; i--) {
        if(B[i]) {
            for(int j = min(n, (i+1)*sq)-1; j >= i*sq; j--)
                if(A[j]) return j;
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_FAILURE);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K; cin >> N;
    vector<int> A = {N};
    for(int i = 0; i < N; i++) {
        int x; cin >> x;
        A.push_back(A.back()+x);
    }
    N++; K = 2*N+1;
    vector<vector<int>> B(K);
    for(int i = 0; i < N; i++) B[A[i]].push_back(i);
    vector<pii> C(N);
    for(int i = 0; i < K; i++) {
        for(int j = 0; j < B[i].size(); j++) {
            if(j == 0) C[B[i][j]].fi = -1;
            else C[B[i][j]].fi = B[i][j-1];
            if(j+1 == B[i].size()) C[B[i][j]].se = -1;
            else C[B[i][j]].se = B[i][j+1];
        }
    }
    //cout << C;
    int q, sq = sqrt(N); cin >> q;
    vector<piii> Q(q);
    for(int i = 0; i < Q.size(); i++) {
        cin >> Q[i].se.fi >> Q[i].se.se;
        Q[i].fi = i; Q[i].se.fi--; Q[i].se.se++;
    }
    sort(Q.begin(), Q.end(), [&](piii &a, piii &b) {
        if(a.se.fi/sq == b.se.fi/sq) return a.se.se < b.se.se;
        return a.se.fi/sq < b.se.fi/sq;
    });
    vector<int> ans(q), dif(K, -1), D(N+1, 0), E((N+1)/sq+1, 0);
    int l = Q[0].se.fi, r = Q[0].se.se;
    for(int i = l; i < r; i++) add_query(A[i], i, sq, C[i].fi, dif, D, E);
    for(int i = 0; i < Q.size(); i++) {
        //cout << Q[i] << "\n";
        while(r < Q[i].se.se) { add_query(A[r], r, sq, C[r].fi, dif, D, E); r++; }
        while(l > Q[i].se.fi) { l--; add_query(A[l], l, sq, C[l].se, dif, D, E); }
        while(r > Q[i].se.se) { r--; sub_query(A[r], r, sq, C[r].fi, dif, D, E); }
        while(l < Q[i].se.fi) { sub_query(A[l], l, sq, C[l].se, dif, D, E); l++; }
        //cout << dif << D << E << "\n";
        ans[Q[i].fi] = find_query(N+1, sq, D, E);
    }
    for(auto i : ans) cout << i << "\n";
    return 0;
}
