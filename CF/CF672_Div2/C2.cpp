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

int chk(int i, vector<int>& A) {
    if(i == 0) {
        if(A[i] > A[i+1]) return 1;
    } else if(i == A.size()-1) {
        if(A[i] > A[i-1]) return 1;
    } else {
        if(A[i] < A[i-1] && A[i] < A[i+1]) return -1;
        if(A[i] > A[i-1] && A[i] > A[i+1]) return 1;
    }
    return 0;
}

int change(int i, vector<int>& A, vector<int>& B) {
    if(i < 0 || i >= A.size()) return 0;
    int tmp = chk(i, A);
    int ans = A[i]*(tmp-B[i]);
    B[i] = tmp;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, q; cin >> n >> q;
        vector<int> A(n), B(n, 0);
        vector<pi> C(q);
        for(auto &i : A) cin >> i;
        for(auto &i : C) cin >> i.fi >> i.se;
        if(n == 1) {
            for(int i = 0; i < q+1; i++) cout << A[0] << "\n";
            continue;
        }
        for(int i = 0; i < n; i++) B[i] = chk(i, A);
        ll ans = 0;
        for(int i = 0; i < n; i++) ans += A[i]*B[i];
        cout << ans << "\n";
        for(auto &i : C) {
            swap(A[--i.fi], A[--i.se]);
            swap(B[i.fi], B[i.se]);
            for(int j = -1; j <= 1; j++) ans += change(j+i.fi, A, B);
            for(int j = -1; j <= 1; j++) ans += change(j+i.se, A, B);
            cout << ans << "\n";
        }
    }
    return 0;
}