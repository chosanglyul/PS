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

bool cmp(vector<ll>& A, vector<ll>& B) {
    return A.size() > B.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<vector<ll>> A(n), D;
        vector<ll> B(n), C(n);
        for(auto &i : B) cin >> i;
        for(auto &i : C) cin >> i;
        for(int i = 0; i < n; i++) A[--B[i]].push_back(C[i]);
        for(auto &i : A) sort(i.begin(), i.end(), greater<ll>());
        sort(A.begin(), A.end(), cmp);
        for(int i = 0; i < n; i++) {
            if(A[i].size()) D.push_back(vector<ll>());
            else break;
            for(auto j : A[i]) {
                if(D[i].empty()) D[i].push_back(j);
                else D[i].push_back(D[i].back()+j);
            }
        }
        for(int i = 0; i < n; i++) {
            ll ans = 0LL;
            for(int j = 0; j < D.size(); j++) {
                if(D[j].size() <= i) break;
                ans += D[j][D[j].size()-1-D[j].size()%(i+1)];
            }
            cout << ans << " ";
        }
        cout << "\n";
    }
    return 0;
}