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

struct Node {
    vector<pair<char, Node*>> nxt;
    int cnt = 0;
};

ll solve(Node* head) {
    ll ans = 1LL;
    for(auto &i : head->nxt)
        ans = mod(ans*solve(i.se), P);
    for(int i = 1; i <= head->cnt; i++)
        ans = mod(ans*i, P);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Node* head = new Node();
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        Node* tmp = head;
        for(auto j : s) {
            Node* nxt = nullptr;
            for(auto &k : tmp->nxt) {
                if(k.fi == j) {
                    nxt = k.se;
                    break;
                }
            }
            if(!nxt) {
                tmp->nxt.push_back({j, new Node()});
                nxt = tmp->nxt.back().se;
                tmp->cnt++;
            }
            tmp = nxt;
        }
        tmp->cnt++;
    }
    cout << solve(head) << "\n";
    return 0;
}