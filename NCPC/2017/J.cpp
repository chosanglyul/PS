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
    int l, r; cin >> l >> r;
    if(l == 0 && r == 0) {
        cout << "Not a moose\n";
    } else if (l == r) {
        cout << "Even " << l+r << "\n";
    } else {
        cout << "Odd " << max(l, r) * 2 << "\n";
    }
    return 0;
}