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

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n; cin >> n;
    vector<pii> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    int p; cin >> p;
    vector<int> B(p);
    for(auto &i : B) cin >> i;
    vector<vector<int>> E(n);
    for(int i = 0; i < n; i++) {
        int s = lower_bound(B.begin(), B.end(), A[i].fi) - B.begin();
        int e = upper_bound(B.begin(), B.end(), A[i].se) - B.begin();
        if(e - s > 2) {
            cout << "impossible\n";
            return 0;
        }
        for(int j = s; j < e; j++) E[i].push_back(B[j]);
    }
    vector<int> C;
    for(int i = 0; i < n; i++) {
        if(E[i].size() == 2) continue;
        else if(E[i].empty() || E[i].back() != A[i].se) {
            if(i+1 < n && A[i].se == A[i+1].fi && E[i+1].size() < 2) {
                E[i].push_back(A[i].se);
                E[i+1].push_back(A[i+1].fi);
                sort(E[i+1].begin(), E[i+1].end());
                C.push_back(A[i].se);
            }
        }
        for(int j = A[i].fi+1; j < A[i].se && E[i].size() < 2; j++) {
            auto iter = lower_bound(E[i].begin(), E[i].end(), j);
            if(iter < E[i].end() && *iter == j) continue;
            E[i].push_back(j);
            C.push_back(j);
            sort(E[i].begin(), E[i].end());
        }
    }
    cout << C.size() << "\n";
    for(auto i : C) cout << i << " ";
    cout << "\n";
    return 0;
}