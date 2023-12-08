#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        int a = 0, b = 0;
        for(int i = 0; i < m; i++) {
            int x, y; cin >> x >> y;
            a = max(x, a), b = max(y, b);
        }
        if(a+b > n) {
            cout << "IMPOSSIBLE\n";
        } else {
            for(int i = 0; i < a; i++) cout << 'R';
            for(int i = 0; i < n-a; i++) cout << 'W';
            cout << "\n";
        }
    }
    return 0;
}