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
        int n, k; cin >> n >> k;
        vector<char> A(n);
        for(auto &i : A) cin >> i;
        bool can = true;
        for(int i = 0; i < k; i++) {
            char tmp = A[i];
            for(int j = i+k; j < n; j += k) {
                if(tmp == '?') tmp = A[j];
                else if(A[j] != '?' && A[j] != tmp) can = false;
            }
            if(can) {
                for(int j = i; j < n; j += k)
                    A[j] = tmp;
            }
        }
        int c0 = 0, c1 = 0;
        for(int i = 0; i < k; i++) {
            if(A[i] == '0') c0++;
            else if(A[i] == '1') c1++;
        }
        if(c0 > k/2 || c1 > k/2) can = false;
        if(can) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}