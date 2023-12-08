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
const int P = 1000;
const ll LLINF = (ll)1e18+1;
template <typename T>
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

int mod(int a, int b) { return ((a%b) + b) % b; }

typedef vector<vector<int>> mat;

mat matmul(mat &a, mat &b) {
    mat c(a.size(), vector<int>(b[0].size(), 0));
    for(int i = 0; i < a.size(); i++)
        for(int j = 0; j < b[0].size(); j++)
            for(int k = 0; k < b.size(); k++)
                c[i][j] = mod(c[i][j]+a[i][k]*b[k][j], P);
    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; ll b; cin >> n >> b;
    mat A(n, vector<int>(n, 0));
    for(auto &i : A) for(auto &j : i) cin >> j;
    mat B(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) B[i][i] = 1;
    while(b) {
        if(b&1) B = matmul(A, B);
        A = matmul(A, A);
        b >>= 1;
    }
    for(auto &i : B) cout << i;
    return 0;
}
