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

vector<int> de_bruijn(int K, int N, int L) {
    vector<int> ans, tmp;
    function<void(int)> dfs = [&](int T) {
        if((int)ans.size() >= L) return;
        if((int)tmp.size() == N) {
            if(N%T == 0)
                for(int i = 0; i < T && (int)ans.size() < L; i++)
                    ans.push_back(tmp[i]);
        } else {
            int k = ((int)tmp.size()-T >= 0 ? tmp[(int)tmp.size()-T] : 1);
            tmp.push_back(k);
            dfs(T);
            tmp.pop_back();
            for(int i = k+1; i <= K; i++) {
                tmp.push_back(i);
                dfs((int)tmp.size());
                tmp.pop_back();
            }
        }
    };
    dfs(1);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, K; cin >> N >> M >> K;
    vector<int> A = de_bruijn(M, N, K+N-1);
    int idx = 0;
    while(A.size() < K+N-1) A.push_back(A[idx++]);
    vector<int> B(M);
    for(auto &i : B) cin >> i;
    for(auto i : A) cout << B[i-1];
    cout << "\n";
    return 0;
}
