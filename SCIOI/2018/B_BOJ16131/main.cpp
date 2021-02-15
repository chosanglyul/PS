#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, a, b, m; cin >> n >> a >> b >> m;
    --a;
    vector<int> A(n), B(n), C(n);
    int cnt = 0, len = 0, malen = 0;
    for(int i = 0; i < n; i++) B[i] = i;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) C[B[j]] = j;
        if(abs(C[a]-C[0]) <= b) {
            cnt++, len++;
        } else {
            malen = max(len, malen);
            len = 0;
        }
        if(i == m-1) {
            malen = max(len, malen);
            break;
        }
        for(auto &j : A) cin >> j;
        for(auto &j : A) {
            int tmp; cin >> tmp;
            j -= tmp;
        }
        for(int j = 0; j < n-1; j++) {
            if((A[B[j+1]] >= 0 && A[B[j]] < 0) || (A[B[j+1]] >= 0 && A[B[j]] >= 0 && A[B[j+1]] >= A[B[j]]+2) || (A[B[j+1]] < 0 && A[B[j]] < 0 && A[B[j+1]] >= A[B[j]]+4)) {
                A[B[j]] += 2;
                A[B[j+1]] -= 2;
                swap(B[j], B[j+1]);
            }
        }
    }
    cout << cnt << " " << malen << "\n";
    return 0;
}