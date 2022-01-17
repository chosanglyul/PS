#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
#define fi first
#define se second
const int INF = 2e9+5;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> A(n);
    set<pi> S;
    for(int i = 0; i < n; i++) {
        cin >> A[i];
        S.insert({A[i], i});
    }
    int ans = 0;
    while(S.size()) {
        pi tmp = *S.begin();
        S.erase(tmp);
        A[tmp.se] = INF;
        int l = tmp.se, r = tmp.se;
        while(--l >= 0 && A[l] <= tmp.fi+k) {
            S.erase({A[l], l});
            A[l] = INF;
        }
        while(++r < n && A[r] <= tmp.fi+k) {
            S.erase({A[r], r});
            A[r] = INF;
        }
        ans++;
    }
    cout << ans << "\n";
    return 0;
}