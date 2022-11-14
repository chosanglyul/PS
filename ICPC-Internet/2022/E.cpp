#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, b, a; cin >> n >> b >> a;
    vector<int> A(n);
    for(int i = 0; i < n; i++) cin >> A[i];
    sort(A.begin(), A.end());
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(i >= a) b -= A[i-a]/2;
        b -= A[i]/2;
        if(b >= 0) cnt++;
        else break;
    }
    cout << cnt << "\n";
    return 0;
}