#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int A[101010];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, q; cin >> n >> k >> q;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        A[i] = x == k;
    }
    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        ll cnt = 0LL;
        for(int j = 0; j < x; j++)
            for(int k = j; k < x; k++, cnt++)
                if(A[k]) break;
        cout << cnt << "\n";
    }
    return 0;
}