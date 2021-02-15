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
        ll n; cin >> n;
        vector<pl> A;
        for(ll i = 2; i*i <= n; i++) {
            if(n%i == 0) {
                A.push_back({0, i});
                while(n%i == 0) {
                    A[A.size()-1].fi++;
                    n /= i;
                }
            }
        }
        if(n > 1) A.push_back({1, n});
        sort(A.begin(), A.end());
        vector<ll> B(A.back().fi, 1);
        for(auto &i : A) {
            for(int j = 0; j < i.fi; j++) {
                B[j] *= i.se;
            }
        }
        reverse(B.begin(), B.end());
        cout << B.size() << "\n";
        for(ll i : B) cout << i << " ";
        cout << "\n";
    }
    return 0;
}