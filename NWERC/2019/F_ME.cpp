#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+5;
const int P = 1000000007;
const ll LLINF = (ll)1e18+5;

class uf {
    vector<int> P;

    public:
    uf(int n) {
        P.resize(n);
        for(int i = 0; i < n; i++) P[i] = i;
    }
    void mer(int x, int y) {
        x = fin(x), y = fin(y);
        P[x] = y;
    }
    int fin(int x) {
        if(P[x] == x) return x;
        return P[x] = fin(P[x]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    uf U(n);
    vector<vector<int>> A(n);
    vector<int> B;
    for(auto &i : A) {
        int x; cin >> x;
        i.resize(x);
        for(auto &j : i) {
            cin >> j;
            B.push_back(j);
        }
    }
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());
    for(auto &i : A) for(auto &j : i) j = lower_bound(B.begin(), B.end(), j) - B.begin();
    vector<int> C(B.size(), -1);
    vector<piii> P;
    for(int i = 0; i < n; i++) {
        for(auto j : A[i]) {
            if(C[j] == -1) C[j] = i;
            else if(U.fin(i) != U.fin(C[j])) {
                P.push_back({j, {i, C[j]}});
                U.mer(i, C[j]);
            }
        }
    }
    int tmp = U.fin(0);
    for(int i = 0; i < n; i++) {
        if(U.fin(i) != tmp) {
            cout << "impossible\n";
            return 0;
        }
    }
    for(auto &i : P) cout << i.se.fi+1 << " " << i.se.se+1 << " " << B[i.fi] << "\n";
    return 0;
}