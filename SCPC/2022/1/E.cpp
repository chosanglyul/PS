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
        vector<vector<int>> chk(n, vector<int>(n));
        for(auto &i : chk) for(auto &j : i) {
            char c; cin >> c;
            j = (c == '.');
        }

        vector<vector<int>> S(n, vector<int>(n));
        for(int i = 0; i < n; i++) {
            for(int j = 0, lst = -1; j < n; j++) {
                if(chk[i][j]) S[i][j] = lst+1;
                else lst = j;
            }
        }

        vector<vector<pi>> C(n, vector<pi>(n));
        for(int i = 0; i < n; i++) {
            int cnt = 0;
            for(int j = 0; j < n; cnt += chk[i][j++]) C[i][j].fi = cnt;
            for(int j = 0; j < n; j++) C[i][j].se = cnt - C[i][j].fi - chk[i][j];
        }

        ll ans = 0LL;
        vector<vector<pi>> D(n, vector<pi>(n));
        for(int i = 0; i < n; i++) {
            for(int j = 0, s = -1, e = -1; j < n; j++) {
                if(chk[i][j]) {
                    if(i && chk[i-1][j]) {
                        e = j;
                        if(s < 0) s = e;
                    }
                    if(s >= 0) {
                        D[i][j].fi = D[i-1][s].fi;
                        D[i][j].se = D[i-1][e].se;
                    } else D[i][j] = {0, 0};
                    D[i][j].fi += C[i][S[i][j]].fi;
                    ans += D[i][j].fi+D[i][j].se;
                    D[i][j].se += C[i][j].se;
                } else s = e = -1;
            }
        }
        cout << "Case #" << _t+1 << "\n";
        cout << ans << "\n";
    }
    return 0;
}