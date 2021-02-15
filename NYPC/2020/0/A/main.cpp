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
    int n; cin >> n;
    vector<ll> A(n), B(n);
    for(auto &i : A) cin >> i;
    B[0] = A[0];
    for(int i = 1; i < n; i++) {
        if(A[i-1] < 0) B[i] = A[i]+max(B[i-1], 0LL);
        else B[i] = B[i-1]+A[i];
    }
    ll maxv = -LLINF;
    for(int i = 0; i < n; i++) maxv = max(maxv, B[i]);
    cout << maxv << endl;
    return 0;
}