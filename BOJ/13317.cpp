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
    int n = 50, m = n-1;
    cout << n << " " << m << "\n";
    for(int i = m-1; i >= 0; i--)
        cout << i+1 << " " << i+2 << " -1\n";
    return 0;
}