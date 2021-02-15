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
    for(int i = 0; i < t; i++) {
        int n; cin >> n;
        vector<int> A(n);
        for(auto &i : A) cin >> i;
        reverse(A.begin(), A.end());
        for(auto &i : A) cout << i << " ";
        cout << "\n";
    }
    return 0;
}