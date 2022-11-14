#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<string> S(n);
    vector<double> A(n), B(n);
    for(int i = 0; i < n; i++) cin >> S[i] >> A[i] >> B[i];
    double mi = (double)INF;
    vector<int> ans(4, -1);
    for(int i = 0; i < n; i++) {
        vector<pair<double, int>> T;
        for(int j = 0; j < n; j++) {
            if(j == i) continue;
            T.push_back({B[j], j});
        }
        sort(T.begin(), T.end());
        double tmp = A[i]+T[0].fi+T[1].fi+T[2].fi;
        if(tmp < mi) {
            mi = tmp;
            ans = {i, T[0].se, T[1].se, T[2].se};
        }
    }
    cout << mi << "\n"; 
    for(auto i : ans) cout << S[i] << "\n";
    return 0;
}