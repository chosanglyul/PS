#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+5;
const int P = 1000000007;
const ll LLINF = (ll)1e18+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<int> B(A);
    sort(B.begin(), B.end());
    if(A == B) cout << "1 1\n";
    else {
        int l = 0, r = n-1;
        while(A[l] == B[l]) l++;
        while(A[r] == B[r]) r--;
        reverse(A.begin()+l, A.begin()+r+1);
        if(A == B) cout << l+1 << " " << r+1 << "\n";
        else cout << "impossible\n";
    }
    return 0;
}