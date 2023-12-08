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
    int n, m; cin >> n >> m;
    set<int> S;
    for(int i = 1; i <= n+m; i++) S.insert(i);
    vector<int> A(n), B(m);
    for(auto &i : A) {
        cin >> i;
        if(i) S.erase(i);
    }
    for(auto &i : B) {
        cin >> i;
        if(i) S.erase(i);
    }
    int a = 0, b = 0;
    while(a < n && A[a]) a++;
    while(b < m && B[b]) b++;
    while(a < n || b < m) {
        int c = *S.begin();
        int x = a, y = b;
        while(x < n && A[x] == 0) x++;
        while(y < m && B[y] == 0) y++;
        if((a && A[a-1] > c) || (b && B[b-1] > c)) {
            if(!b) B[b] = c;
            else if(!a || A[a-1] < B[b-1]) A[a] = c;
            else B[b] = c;
        } else {
            if(a == n) B[b] = c;
            else if(b == m) A[a] = c;
            else if(x == n) B[b] = c;
            else if(y == m || A[x] < B[y]) A[a] = c;
            else B[b] = c;
        }
        S.erase(c);
        while(a < n && A[a]) a++;
        while(b < m && B[b]) b++;
    }
    for(auto i : A) cout << i << " ";
    cout << "\n";
    for(auto i : B) cout << i << " ";
    cout << "\n";
    return 0;
}