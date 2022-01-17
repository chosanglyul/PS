#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    pi a, b; cin >> a.fi >> a.se >> b.fi >> b.se;
    if(n == 1 || m == 1) cout << (a == b ? "YES" : "NO") << "\n";
    else cout << (((a.fi+a.se)%2 == (b.fi+b.se)%2) ? "YES" : "NO") << "\n";
    return 0;
}