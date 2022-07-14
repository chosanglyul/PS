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
const int P = 10080;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll l; cin >> l;
    string x;
    getline(cin, x, '\n');
    int m = stoi(x);
    vector<string> ans, T;
    ll pri = LLINF;
    for(int i = 0; i < m; i++) {
        getline(cin, x, '\n');
        for(int i = 0, j = 0; i <= x.size(); i++) {
            if(i == x.size() || x[i] == ',') {
                string ss;
                for(int k = j; k < i; k++) ss.push_back(x[k]);
                T.push_back(ss);
                j = i+1;
            }
        }
        string s = T[0];
        ll p = stoi(T[1]), c = stoi(T[2]), t = stoi(T[3]), r = stoi(T[4]);
        T.clear();
        int cnt = 0;
        queue<ll> Q;
        for(int j = 0; j < 10080; j++) {
            Q.push(j%(t+r));
            if(Q.back() < t) cnt++;
        }
        vector<ll> A;
        for(int j = 0; j < t+r; j++) {
            A.push_back(cnt);
            if(Q.front() < t) cnt--;
            Q.push((Q.back()+1)%(t+r));
            if(Q.back() < t) cnt++;
            Q.pop();
        }
        ll tmp = 0LL;
        while(tmp < l) tmp += t+r;
        tmp %= l;
        ll tt = 0LL, shi = 0LL, ju = 0LL;
        bool can = true;
        do {
            ju++;
            tt += A[shi];
            shi = (shi+tmp)%(t+r);
            if(tt*c < ju*l) can = false;
        } while(shi);
        if(can) {
            if(pri > p) {
                ans.clear();
                pri = p;
                ans.push_back(s);
            } else ans.push_back(s);
        }
    }
    if(ans.size()) for(auto &i : ans) cout << i << "\n";
    else cout << "no such mower\n";
    return 0;
}