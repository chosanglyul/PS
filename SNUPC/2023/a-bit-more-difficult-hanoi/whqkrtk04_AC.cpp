#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P = 1'000'000'007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> A(n), B(n+1); B[1] = 1;
    for(auto &i : A) cin >> i;
    for(int i = 2; i <= n; i++) B[i] = (B[i-1]*2)%P;
    int ans = 0;
    while(A.size()) {
        if(A.back() != k) {
            ans = (ans+B[A.size()])%P;
            k = 6-A.back()-k;
        }
        A.pop_back();
    }
    cout << ans << "\n";
    return 0;
}
