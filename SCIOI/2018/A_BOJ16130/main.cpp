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
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        int cnt = 0, last = 0, len = 0;
        for(auto j : s) {
            if(j > '9') cnt += j-'A'+10;
            else cnt += j-'0';
            if((cnt-last) >= 10) {
                last = (cnt/10)*10;
                if(last/10 >= 4) break;
                else len += (last/10);
            }
        }
        cout << len;
        if(last/10 > 4) cout << "(09)\n";
        else if(last/10 == 4) cout << "(weapon)\n";
        else cout << "\n";
    }
    return 0;
}