#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> A(n), B(m);
    for (int i=0; i<n; ++i) cin >> A[i];
    for (int i=0; i<m; ++i) cin >> B[i];

    vector<tuple<int, int, int>> conds;
    for (int i=0; i<n; ++i) {
        if (A[i] != 0) conds.push_back({ A[i], 0, i });
    }
    for (int i=0; i<m; ++i) {
        if (B[i] != 0) conds.push_back({ B[i], 1, i });
    }
    conds.push_back({ n+m+1, 0, n });
    conds.push_back({ n+m+2, 1, m });
    sort(conds.begin(), conds.end());

    int val_cnt = 1;
    vector<int> filled(n+m+3, 0);
    for (int i=0; i<n; ++i) filled[A[i]] = 1;
    for (int i=0; i<m; ++i) filled[B[i]] = 1;
    auto next_num = [&]() {
        while (filled[val_cnt]) val_cnt++;
        return val_cnt++;
    };

    int p1 = 0, p2 = 0;
    vector<int> Aans(n+1), Bans(m+1);
    for (int i=0; i<conds.size(); ++i) {
        auto[v, arr, idx] = conds[i];
        if (arr == 0) {
            for (; p1<idx; ++p1) Aans[p1] = next_num();
            Aans[p1++] = v;
        } else {
            for (; p2<idx; ++p2) Bans[p2] = next_num();
            Bans[p2++] = v;
        }
    }

    for (int i=0; i<n; ++i) cout << Aans[i] << ' ';
    cout << '\n';
    for (int i=0; i<m; ++i) cout << Bans[i] << ' ';
    cout << '\n';

    return 0;
}