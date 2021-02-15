#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

int dp[1010][1010];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string a, b; cin >> a >> b;
    for(int i = 1; i <= a.size(); i++) {
        for(int j = 1; j <= b.size(); j++) {
            if(a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1]+1;
            dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i][j-1]));
        }
    }
    cout << dp[a.size()][b.size()] << "\n";
    string c = "";
    for(int i = a.size(), j = b.size(); i > 0 && j > 0;) {
        if(dp[i][j] == dp[i-1][j]) --i;
        else if(dp[i][j] == dp[i][j-1]) --j;
        else { c.push_back(a[--i]); --j; }
    }
    reverse(c.begin(), c.end());
    cout << c << "\n";
    return 0;
}