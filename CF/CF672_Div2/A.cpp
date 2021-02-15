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
const int P = 1e9+7;
const ll LLINF = 1e18+1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> A(n);
        bool can = false;
        for(auto &i : A) cin >> i;
        for(int i = 0; i < n-1; i++) {
            if(A[i] <= A[i+1]) {
                can = true;
            }
        }
        if(can) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}