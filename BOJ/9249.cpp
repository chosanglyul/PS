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

// 0-base index
// sa[i]: S[i..n-1]이 i번째 사전순으로 작은 suffix임을 의미함
// lcp[i]: sa[i]와 sa[i+1]이 나타내는 suffix간 lcp임. lcp[n-1]은 undefined.
void suffix_array(string S, vector<int> &sa, vector<int> &lcp) {
    int n = S.size();
    vector<int> r(n), nr(n), pos(n), ind(n);
    sa.resize(n); lcp.resize(n);

    for (int i = 0; i < n; i++) sa[i] = i;
    sort(sa.begin(), sa.end(), [&](int a, int b) { return S[a] < S[b]; });
    for (int i = 1; i < n; i++) r[sa[i]] = r[sa[i - 1]] + (S[sa[i - 1]] != S[sa[i]]);

    for (int d = 1; d < n; d <<= 1) {
        for (int i = n - 1; i >= 0; i--) {
            pos[r[sa[i]]] = i;
        }
        int j = 0;
        for (int i = n - d; i < n; i++) ind[j++] = i;
        for (int i = 0; i < n; i++) {
            if (sa[i] >= d) ind[j++] = sa[i] - d;
        }
        for (int i = 0; i < n; i++) {
            sa[pos[r[ind[i]]]++] = ind[i];
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
    vector<int> sa, lcp;
    string t, s; cin >> t >> s;
    string tmp;
    for(auto i : t) tmp.push_back(i);
    tmp.push_back('$');
    for(auto i : s) tmp.push_back(i);
    suffix_array(tmp, sa, lcp);
    lcp.pop_back();
    int id = -1;
    for(int i = 0; i < lcp.size(); i++) {
        if(max(sa[i], sa[i+1]) > t.size() && min(sa[i], sa[i+1]) < t.size()) {
            if(id == -1 || lcp[id] < lcp[i]) id = i;
        }
    }
    cout << lcp[id] << "\n";
    for(int i = 0; i < lcp[id]; i++) cout << tmp[sa[id]+i];
    cout << "\n";
    return 0;
}