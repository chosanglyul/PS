#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+5;

ll dnc(int s, int e, vector<int>& A) {
    if(s+1 == e) return A[s];
    int mi = s+e>>1;
    ll ans = max(dnc(s, mi, A), dnc(mi, e, A));
    for(int i = mi, j = mi, h = INF; i > s || j < e;) {
        if(i == s) h = min(A[j++], h);
        else if(j == e || A[i-1] >= A[j]) h = min(A[--i], h);
        else h = min(A[j++], h);
        //cout << i << " " << j << " " << h << "\n";
        ans = max(ans, (ll)(j-i)*h);
    }
    return ans;
}

int solve() {
    int n; cin >> n;
    if(n == 0) return 0;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    cout << dnc(0, n, A) << "\n";
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(solve());
    return 0;
}