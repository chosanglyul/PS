#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second
const int INF = (int)1e9+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<ll> A(n);
    for (ll &tmp: A) cin >> tmp;

    vector<ll> S(2e6);
    for (int i = 1; i < S.size(); ++i) {
        S[i] = (ll)i*(i-1)/2 + 1;
    }

    ll d = 0LL;
    while(true) {
        int k = upper_bound(S.begin(), S.end(), A[0]) - S.begin() - 1;
        vector<int> I(5+A.back()/k);
        for(int i = 0; i < I.size(); i++)
            I[i] = lower_bound(A.begin(), A.end(), S[i+k]-d) - A.begin();
        ll ma = 0LL;
        for(int i = 0; i+1 < I.size(); i++) {
            int idx = k+i;
            if(idx%2 == 0) {
                if(I[i+1] - I[i] > 0) {
                    ll x = A[I[i]]+d;
                    x = S[idx+1] - x;
                    ma = max(ma, x);
                }
            }
        }
        if(ma == 0LL) break;
        d += ma;
    }
    cout << d << "\n";
    return 0;
}