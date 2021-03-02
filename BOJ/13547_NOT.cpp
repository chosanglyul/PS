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
const int P = 1000000007;
const ll LLINF = 1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    int m; cin >> m;
    int sq = (int)sqrt(n);
    vector<pii> B(m);
    vector<int> C(m), D(1010101, 0);
    for(int i = 0; i < m; i++) {
        B[i].fi = i;
        cin >> B[i].se.fi >> B[i].se.se;
        B[i].se.fi--;
    }
    sort(B.begin(), B.end(), [&](pii& a, pii& b) {
        if(a.se.fi/sq == b.se.fi/sq) return a.se.se < b.se.se;
        return a.se.fi/sq < b.se.fi/sq;
    });
    int s = B[0].se.fi, e = B[0].se.se;
    int cnt = 0;
    for(int i = s; i < e; i++) {
        if(D[A[i]] == 0) cnt++;
        D[A[i]]++;
    }
    C[B[0].fi] = cnt;
    for(int i = 1; i < m; i++) {
        while(s > B[i].se.fi) {
            s--;
            if(D[A[s]] == 0) cnt++;
            D[A[s]]++;
        }
        while(e < B[i].se.se) {
            if(D[A[e]] == 0) cnt++;
            D[A[e]]++;
            e++;
        }
        while(s < B[i].se.fi) {
            D[A[s]]--;
            if(D[A[s]] == 0) cnt--;
            s++;
        }
        while(e > B[i].se.se) {
            e--;
            D[A[e]]--;
            if(D[A[e]] == 0) cnt--;
        }
        C[B[i].fi] = cnt;
    }
    for(auto &i : C) cout << i << "\n";
    return 0;
}