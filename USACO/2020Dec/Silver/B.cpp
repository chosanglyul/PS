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

vector<pi> I(int n) {
    vector<pi> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    vector<int> X(n), Y(n);
    for(int i = 0; i < n; i++) {
        X[i] = A[i].fi;
        Y[i] = A[i].se;
    }
    sort(X.begin(), X.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
    for(int i = 0; i < n; i++) {
        A[i].fi = lower_bound(X.begin(), X.end(), A[i].fi) - X.begin();
        A[i].se = lower_bound(Y.begin(), Y.end(), A[i].se) - Y.begin();
    }
    return A;
}

vector<vector<int>> p(vector<int>& B) {
    int n = B.size();
    vector<vector<int>> A(n+1, vector<int>(n+1, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            A[i][j] = A[i-1][j]+A[i][j-1]-A[i-1][j-1];
            if(B[i-1] == j-1) A[i][j]++;
        }
    }
    return A;
}

int calc(int x1, int x2, int y1, int y2, vector<vector<int>>& A) {
    return A[x2][y2]-A[x1][y2]-A[x2][y1]+A[x1][y1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pi> A = I(n);
    vector<int> B(n);
    for(auto &i : A) B[i.fi] = i.se;
    vector<vector<int>> C = p(B);
    //cout << " " << C;
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            int x = B[i], y = B[j];
            if(x > y) swap(x, y);
            int a = calc(i+1, j, 0, x, C);
            int b = calc(i+1, j, y+1, n, C);
            ans += (a+1)*(b+1);
        }
    }
    cout << ans+n+1 << endl;
    return 0;
}