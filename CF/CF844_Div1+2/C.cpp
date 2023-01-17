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

int solve(vector<int> &A, vector<int> &B) {
    int ans = 0;
    for(int i = 0; i < 26; i++) ans += abs(A[i]-B[i]);
    return ans/2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        string s; cin >> s;
        vector<int> A(26, 0);
        for(int i = 0; i < n; i++) A[s[i]-'a']++;
        sort(A.begin(), A.end(), greater<int>());
        int ans = INF, idx = 1;
        for(int i = 1; i <= 26; i++) {
            if(n%i == 0) {
                vector<int> B(i, n/i);
                while(B.size() < 26) B.push_back(0);
                int tmp = solve(A, B);
                if(tmp < ans) {
                    ans = tmp;
                    idx = i;
                }
            }
        }
        cout << ans << "\n";
        vector<vector<int>> T(26);
        for(int i = 0; i < n; i++) T[s[i]-'a'].push_back(i);
        vector<int> les;
        for(int i = 0; i < 26; i++) if(T[i].size() < n/idx) les.push_back(i);
        sort(les.begin(), les.end(), [&](int a, int b) {
            return T[a].size() < T[b].size();
        });
        for(int i = 0; i < 26; i++) {
            while(T[i].size() > n/idx) {
                int jdx = T[i].back();
                T[i].pop_back();
                int tmp = les.back();
                T[tmp].push_back(jdx);
                //cout << jdx << " " << tmp+'a' << " " << i+'a' << "\n";
                s[jdx] = tmp+'a';
                if(T[tmp].size() == n/idx) les.pop_back();
            }
        }
        for(int i = 0; i < les.size(); i++) {
            while(T[les[i]].size() && T[les[i]].size() < n/idx) {
                int jdx = T[les[i]].back();
                T[les[i]].pop_back();
                int tmp = les.back();
                T[tmp].push_back(jdx);
                //cout << jdx << " " << tmp+'a' << " " << les[i]+'a' << "\n";
                s[jdx] = tmp+'a';
                if(T[tmp].size() == n/idx) les.pop_back();
            }
        }
        cout << s << "\n";
    }
    return 0;
}