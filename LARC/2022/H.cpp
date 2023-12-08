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

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    
    int n;
    cin >> n;
    map<string, int> name;
    for (int i=1; i<=n; ++i) {
        string s;
        cin >> s;
        name[s] = i;
    }

    vector<int> rank_freq(n+1, 0);
    vector<int> max_rank(n+1, 0);
    vector<int> horse_max_rank_freq(n+1, 0);

    int r;
    cin >> r;
    for (int i=0; i<r; ++i) {
        int m, w;
        cin >> m >> w;
        rank_freq[w]++;
        for (int j=0; j<m; ++j) {
            string s;
            cin >> s;
            int x = name[s];
            int before = max_rank[x];
            max_rank[x] = max(max_rank[x], w);
            if (before < max_rank[x]) {
                horse_max_rank_freq[x] = 0;
            }
            if (w == max_rank[x]) {
                horse_max_rank_freq[x]++;
            }
        }
    }

    // cout << rank_freq << max_rank << horse_max_rank_freq;

    vector<int> ans;
    vector<int> rem;
    for (int i=1; i<=n; ++i) {
        if (max_rank[i] == 0) rem.push_back(i);
    }
    for (int rank=1; rank<=n; ++rank) {
        // cout << rank << endl;
        vector<int> cands, tmp;
        for (int i=1; i<=n; ++i) {
            if (max_rank[i] == rank) {
                if (horse_max_rank_freq[i] == rank_freq[rank]) {
                    cands.push_back(i);
                } else {
                    tmp.push_back(i);
                }
            }
        }
        // cout << cands;
        if (!cands.empty()) {
            ans.push_back(cands.back());
            cands.pop_back();
            while (!cands.empty()) {
                rem.push_back(cands.back());
                cands.pop_back();
            }
        } else {
            assert(!rem.empty());
            ans.push_back(rem.back());
            rem.pop_back();
        }
        while (!tmp.empty()) {
            rem.push_back(tmp.back());
            tmp.pop_back();
        }
        // cout << rem;
        // cout << ans;
    }

    for (int x: ans) {
        for (auto[k, v]: name) {
            if (x == v) {
                cout << k << ' ';
            }
        }
    }

    return 0;
}
