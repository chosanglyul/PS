#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pii> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    vector<pii> B;
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++)
            B.push_back({A[i].fi+A[j].fi, A[i].se+A[j].se});
    for(auto &i : A) i.fi *= 2, i.se *= 2;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    int ans = 0;
    for(int i = 0, j = 0; i < B.size(); ) {
        int tmp = 0, k = i;
        while(j < A.size() && A[j] == B[i]) j++, tmp--;
        while(k < B.size() && B[k] == B[i]) k++, tmp += 2;
        ans = max(ans, tmp);
        i = k;
    }
    cout << ans << "\n";
    return 0;
}