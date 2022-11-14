#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    ll a = 0LL, b = 0LL;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(i < 2) {
            if(i == 0) a += x;
            else b += x;
        }
        else if(a <= b) a += x;
        else b += x;
    }
    ll c = max(a, b) - min(a, b);
    vector<int> A = {1, 2, 5, 10, 20, 50, 100};
    reverse(A.begin(), A.end());
    int cnt = 0;
    for(auto i : A) {
        int tmp = c/i;
        c -= i*tmp;
        cnt += tmp;
    }
    cout << cnt << "\n";
    return 0;
}