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
    int n, s, k; cin >> n >> s >> k;
    pi ps = {s, 0};
    vector<pii> A(n);
    for(int i = 0; i < n; i++) {
        cin >> A[i].se.fi;
        A[i].fi = abs(s-A[i].se.fi);
        A[i].se.se = i+1;
    }
    sort(A.begin(), A.end());
    for(int i = 0; i < k; i++) cout << A[i].se.se << " ";
    return 0;
}