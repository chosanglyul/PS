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
        vector<int> A(n);
        for(auto &i : A) cin >> i;
        sort(A.begin(), A.end());
        ll cnt = 0, all = 0;
        for(int x = 1, i = 0; i < n; i++, cnt++) {
            if(A[i]/2 >= x) {
                while(A[i]/2 >= x) x *= 2;
                //cout << i << " " << A[i] << " " << x << " " << cnt << "\n";
                all += cnt*(cnt-1)/2;
                cnt = 0;
            }
        }
        //cout << cnt << "\n";
        all += cnt*(cnt-1)/2;
        cout << all << "\n";
    }
    return 0;
}