#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    int n;
    cin >> n;
    vector<ll> arr(n);
    for (ll& x: arr) cin >> x;

    ll sum = accumulate(arr.begin(), arr.end(), 0ll) / 3;
    vector<ll> ans(n);
    if (n % 3 == 1) {
        for (int i=0; i<n; ++i) {
            ll tmp = 0;
            int j=i+2;
            if (j >= n) j -= n;
            for (int _=0; _<n/3; ++_) {
                tmp += arr[j];
                j += 3;
                if (j >= n) j -= n;
            }
            ans[i] = sum - tmp;
        }
    } else if (n % 3 == 2) {
        for (int i=0; i<n; ++i) {
            ll tmp = 0;
            int j = i+1;
            if (j >= n) j -= n;
            for (int _=0; _<n/3+1; ++_) {
                tmp += arr[j];
                j += 3;
                if (j >= n) j -= n;
            }
            ans[i] = tmp - sum;
        }
    } else {
        vector<ll> basis(n);
        basis[0] = 0;
        basis[1] = 0;
        for (int i=2; i<n; ++i) {
            basis[i] = arr[i-1] - basis[i-1] - basis[i-2];
            // cout << basis[i] << ' ';
        }
        // cout << endl;
        ll a_inf = 1;
        ll b_inf = 1;
        for (int i=1; i<n/3; ++i) {
            a_inf = max(a_inf, 1-basis[3*i]);
            b_inf = max(b_inf, 1-basis[3*i+1]);
        }
        // cout << a_inf << ' ' << b_inf << endl;

        ans[0] = a_inf;
        ans[1] = b_inf;
        for (int i=2; i<n; ++i) {
            ans[i] = arr[i-1] - ans[i-1] - ans[i-2];
        }
    }

    for (int i=0; i<n; ++i) {
        cout << ans[i] << '\n';
    }
}