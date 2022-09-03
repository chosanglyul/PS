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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        int n; cin >> n;
        vector<pi> A(n);
        vector<int> X, Y;
        for(auto &i : A) {
            cin >> i.fi >> i.se;
            X.push_back(i.fi);
            Y.push_back(i.se);
        }
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());
        sort(Y.begin(), Y.end());
        Y.erase(unique(Y.begin(), Y.end()), Y.end());
        vector<vector<int>> EX(X.size()), EY(Y.size());
        for(auto &i : A) {
            i.fi = lower_bound(X.begin(), X.end(), i.fi) - X.begin();
            i.se = lower_bound(Y.begin(), Y.end(), i.se) - Y.begin();
            EX[i.fi].push_back(i.se);
            EY[i.se].push_back(i.fi);
        }
        for(auto &i : EX) sort(i.begin(), i.end());
        for(auto &i : EY) sort(i.begin(), i.end());
        if(n%2 == 1) {
            int xx, yy;
            for(int i = 0; i < X.size(); i++)
                if(EX[i].size()%2) xx = i;
            for(int i = 0; i < Y.size(); i++)
                if(EY[i].size()%2) yy = i;
            EX[xx].erase(find(EX[xx].begin(), EX[xx].end(), yy));
            EY[yy].erase(find(EY[yy].begin(), EY[yy].end(), xx));
        }
        ll ans = 0LL;
        for(auto &x : EX)
            for(int i = 0; i < x.size(); i += 2)
                ans += Y[x[i+1]] - Y[x[i]];
        for(auto &y : EY)
            for(int i = 0; i < y.size(); i += 2)
                ans += X[y[i+1]] - X[y[i]];
        cout << "Case #" << _t+1 << endl;
        cout << ans << endl;
    }
    return 0;
}