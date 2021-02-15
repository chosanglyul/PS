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
        vector<ll> A(n);
        for(auto &i : A) cin >> i;
        ll plussum = 0;
        for(int i = 0; i < n; i++) {
            if(A[i] == 0) continue;
            if(A[i] < 0) {
                if(plussum + A[i] >= 0) plussum += A[i];
                else plussum = 0;
            } else plussum += A[i];
        }
        cout << plussum << "\n";
    }
    return 0;
}