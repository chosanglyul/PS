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
const int P = 10007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

int mod(int a, int b) { return ((a%b) + b) % b; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    int n = s.size();
    vector<vector<int>> A(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) A[i][i] = 1;
    for(int k = 1; k < n; k++) {
        for(int i = 0; i+k < n; i++) {
            A[i][i+k] = mod(A[i+1][i+k] + A[i][i+k-1], P);
            if(s[i] == s[i+k]) A[i][i+k] = mod(A[i][i+k] + 1, P);
            else if(k != 1) A[i][i+k] = mod(A[i][i+k] - A[i+1][i+k-1], P);
        }
    }
    cout << A[0].back();
    return 0;
}