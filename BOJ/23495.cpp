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

// 0-base index
// sa[i]: lexicographically (i+1)'th suffix (of d letters)
// lcp[i]: lcp between sa[i] and sa[i+1]
// r[i]: rank of s[i..n-1] when only consider first d letters
// nr: temp array for next rank
// cnt[i]: number of positions which has i of next rank
// rf[r]: lexicographically first position which suffixes (of d letters) has rank r
// rdx[i]: lexicographically (i+1)'th suffix when only consider (d+1)'th ~ 2d'th letters
void suffix_array(string S, vector<int> &sa, vector<int> &lcp) {
    int n = S.size();
    vector<int> r(n), nr(n), rf(n), rdx(n);
    sa.resize(n); lcp.resize(n);

    for (int i = 0; i < n; i++) sa[i] = i;
    sort(sa.begin(), sa.end(), [&](int a, int b) { return S[a] < S[b]; });
    for (int i = 1; i < n; i++) r[sa[i]] = r[sa[i - 1]] + (S[sa[i - 1]] != S[sa[i]]);

    for (int d = 1; d < n; d <<= 1) {
        for (int i = n - 1; i >= 0; i--) {
            rf[r[sa[i]]] = i;
        }
        int j = 0;
        for (int i = n - d; i < n; i++) rdx[j++] = i;
        for (int i = 0; i < n; i++) {
            if (sa[i] >= d) rdx[j++] = sa[i] - d;
        }
        for (int i = 0; i < n; i++) {
            sa[rf[r[rdx[i]]]++] = rdx[i];
        }
        nr[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (r[sa[i]] != r[sa[i - 1]]) {
                nr[sa[i]] = nr[sa[i - 1]] + 1;
            }
            else {
                int prv = (sa[i - 1] + d >= n ? -1 : r[sa[i - 1] + d]);
                int cur = (sa[i] + d >= n ? -1 : r[sa[i] + d]);
                nr[sa[i]] = nr[sa[i - 1]] + (prv != cur);
            }
        }
        swap(r, nr);
        if (r[sa[n-1]] == n-1) break;
    }
    for (int i = 0, len = 0; i < n; ++i, len = max(len - 1, 0)) {
        if (r[i] == n - 1) continue;
        for (int j = sa[r[i] + 1]; S[i + len] == S[j + len]; ++len);
        lcp[r[i]] = len;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        string s; cin >> s;
        vector<int> sa, lcp;
        suffix_array(s, sa, lcp);
        set<int> S; S.insert(n);
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            int tmp = *S.lower_bound(sa[i]);
            ans[sa[i]] = tmp-sa[i];
            S.insert(sa[i]);
        }
        cout << ans;
    }
    return 0;
}
