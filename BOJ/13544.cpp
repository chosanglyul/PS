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

void mergesort(vector<int>& A, int s, int e, int d, vector<vector<int>>& mst) {
    while(mst.size() < d+1) mst.push_back(A);
    if(s+1 == e) return;
    int mi = s+e>>1;
    mergesort(A, s, mi, d+1, mst);
    mergesort(A, mi, e, d+1, mst);
    int i = s, j = mi, k = s;
    while(i < mi && j < e) {
        if(mst[d+1][i] < mst[d+1][j]) mst[d][k++] = mst[d+1][i++];
        else mst[d][k++] = mst[d+1][j++];
    }
    while(i < mi) mst[d][k++] = mst[d+1][i++];
    while(j < e) mst[d][k++] = mst[d+1][j++];
}

int query(vector<vector<int>>& mst, int s, int e, int d, int l, int r, int k) {
    if(e <= l || r <= s) return 0;
    else if(l <= s && e <= r) return mst[d].begin()+e-upper_bound(mst[d].begin()+s, mst[d].begin()+e, k);
    else return query(mst, s, s+e>>1, d+1, l, r, k)+query(mst, s+e>>1, e, d+1, l, r, k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    vector<vector<int>> mst;
    for(auto &i : A) cin >> i;
    mergesort(A, 0, n, 0, mst);
    int m, lst = 0; cin >> m;
    while(m--) {
        int a, b, c;
        cin >> a >> b >> c;
        a ^= lst, b ^= lst, c ^= lst;
        a--;
        lst = query(mst, 0, n, 0, a, b, c);
        cout << lst << "\n";
    }
    return 0;
}