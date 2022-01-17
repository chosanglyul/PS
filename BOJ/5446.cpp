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

struct Node {
    map<char, int> nxt;
    bool era = true, ed = false;
    char ch;

    Node(char c) { ch = c; }
};

int solve(int x, vector<Node>& T, string& s) {
    if(T[x].era) {
        //cout << x << " " << s << " " << T[x].ch << "\n";
        return 1;
    }
    int ans = 0;
    for(auto it = T[x].nxt.begin(); it != T[x].nxt.end(); it++) {
        s.push_back(it->fi);
        ans += solve(it->se, T, s);
        s.pop_back();
    }
    if(T[x].ed) ans++;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        vector<Node> T(1, Node('$'));
        int n; cin >> n;
        for(int i = 0; i < n; i++) {
            string s; cin >> s;
            int tmp = 0;
            for(auto i : s) {
                if(T[tmp].nxt[i] == 0) {
                    T[tmp].nxt[i] = T.size();
                    T.push_back(Node(i));
                }
                tmp = T[tmp].nxt[i];
            }
            T[tmp].ed = true;
        }
        int m; cin >> m;
        for(int i = 0; i < m; i++) {
            string s; cin >> s;
            int tmp = 0;
            T[tmp].era = false;
            for(auto i : s) {
                if(T[tmp].nxt.find(i) == T[tmp].nxt.end()) break;
                tmp = T[tmp].nxt[i];
                T[tmp].era = false;
            }
        }
        string ss;
        cout << solve(0, T, ss) << "\n";
    }
    return 0;
}