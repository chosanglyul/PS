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
        vector<int> A(n), B(n);
        for(auto &i : A) cin >> i;
        int m = INF;
        bool can = true;
        for(int i = 0; i < n; i++) {
            m = min(m, A[i]);
            if(i == 0) {
                A[i] = 0;
            } else if(A[i-1] > A[i]) {
                can = false;
                break;
            } else if(A[i-1] > A[i]-m) {
                m = A[i]-A[i-1];
                A[i] = A[i-1];
            } else {
                A[i] = A[i]-m;   
            }
        }
        if(!can) {
            cout << "NO\n";
            continue;
        }
        for(int i = 1; i < n; i++) {
            if(A[i-1] > A[i]) can = false;
        }
        cout << (can ? "YES" : "NO") << "\n";
    }
    return 0;
}