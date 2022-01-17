#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    const int MAX = 10101;
    int n, q; cin >> n >> q;
    vector<pii> A(n);
    for(auto &i : A) cin >> i.se.fi >> i.fi >> i.se.se;
    for(int i = 0; i < q; i++) {
        int s, e, x, y; cin >> s >> e >> x >> y; --s;
        vector<int> B(MAX, 1);
        for(int i = s; i < e; i++) {
            int tmp = 0;
            for(int j = A[i].se.fi; j < A[i].se.se; j++) {
                tmp += B[j];
                B[j] = 0;
            }
            B[A[i].fi] = tmp;
        }
        int ans = 0;
        for(int i = x; i < y; i++) ans += B[i];
        cout << ans << "\n";
    }
    return 0;
}