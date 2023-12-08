#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, k; cin >> n >> k;
    if(k == 0LL) {
        cout << "YES\n";
        for(ll i = 2LL; i <= n; i++)
            cout << "1 " << i << "\n";
        return 0;
    }
    if(n == 4LL) {
        if(k == 1LL) {
            cout << "YES\n";
            cout << "1 2\n";
            cout << "2 3\n";
            cout << "3 4\n";
        } else cout << "NO\n";
        return 0;
    }

    for(ll b = 0LL; b <= n-5LL; b++) {
        ll tmp = b*(n-5LL-b)+n-5LL;
        ll c = k-tmp-2LL;
        if(0LL <= c && c <= n-5LL-b) {
            ll a = n-5LL-b-c;
            cout << "YES\n";
            cout << "1 2\n";
            cout << "2 3\n";
            cout << "3 4\n";
            cout << "4 5\n";
            ll cnt = 6LL;
            for(ll j = 0LL; j < a; j++, cnt++) cout << "1 " << cnt << "\n";
            for(ll j = 0LL; j < b; j++, cnt++) cout << "2 " << cnt << "\n";
            for(ll j = 0LL; j < c; j++, cnt++) cout << "3 " << cnt << "\n";
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}
