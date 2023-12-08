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

const int MAXM = 50;
template <int MAXN>
struct eertree {
    struct Node {
        int len = 0, link = 0;
        array<int, MAXN> nxt;
        array<bool, MAXM> cnt;
        Node() {
            fill(nxt.begin(), nxt.end(), -1);
            fill(cnt.begin(), cnt.end(), false);
        }
    };

    vector<int> S;
    vector<Node> V;
    int root = 0, idx = 0;

    eertree() {
        V.resize(2);
        V[0].len = -1;
    }
    
    void add(int c) {
        S.push_back(c);
        for(int tmp = root; ; tmp = V[tmp].link) {
            auto iter = S.rbegin()+V[tmp].len+1;
            if(iter < S.rend() && *iter == c) {
                if(V[tmp].nxt[c] == -1) {
                    root = V.size();
                    V[tmp].nxt[c] = root;
                    V.push_back(Node());
                    V.back().len = V[tmp].len+2;
                    tmp = V[tmp].link;
                    iter = S.rbegin()+V[tmp].len+1;
                    while(iter >= S.rend() || *iter != c) {
                        tmp = V[tmp].link;
                        iter = S.rbegin()+V[tmp].len+1;
                    }
                    tmp = V[tmp].nxt[c];
                    if(V.back().len == 1 || tmp <= 0) V.back().link = 1;
                    else V.back().link = tmp;
                } else root = V[tmp].nxt[c];
                V[root].cnt[idx] = true;
                break;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    eertree<26> T;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(auto c : s) T.add(c-'a');
        T.idx++, T.root = 0, T.S.clear();
    }
    int ans = 0;
    for(auto &v : T.V) {
        bool can = true;
        for(int i = 0; i < n; i++)
            can = can && v.cnt[i];
        if(can) ans = max(ans, v.len);
    }
    cout << ans << "\n";
    return 0;
}
