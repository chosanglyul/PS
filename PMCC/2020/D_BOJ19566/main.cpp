#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    vector<ll> A(n), B(n);
    for(auto &i : A) {
        cin >> i;
        i -= k;
    }
    B[0] = A[0];
    for(int i = 1; i < n; i++)
        B[i] = B[i-1]+A[i];
    sort(B.begin(), B.end());
    ll ans = (B[0] == 0), cnt = 1;
    for(int i = 1; i < n; i++, cnt++) {
        if(B[i] == 0) ans++;
        if(B[i] != B[i-1]) {
            ans += (cnt*(cnt-1))/2;
            cnt = 0;
        }
    }
    ans += (cnt*(cnt-1))/2;
    cout << ans << "\n";
    return 0;
}