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
const int P = 1e9+7;
const ll LLINF = 1e18+1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int a, b; cin >> a >> b;
        string s; cin >> s;
        int n = a/b, cnt = 0;
        for(int i = 0; i < s.size(); i++) {
            if(i == 0) {
                if(s[i] == '1') cnt += a;
            } else if(s[i] == '1' && s[i-1] == '0') cnt += a;
        }
        //cout << cnt << " " << n << "\n";
        int lst = -1;
        for(int i = 0, tmp = 0; i < s.size(); i++, tmp++) {
            if(s[i] == '1') {
                if(lst != -1 && s[i-1] != '1') {
                    int c = i-lst-1;
                    if(c <= n) cnt += b*c-a;
                }
                lst = i;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}