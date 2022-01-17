#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __uint128_t lll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1e9;
const ll LLIII = (ll)1e12+1e9;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

int binsea(lll a, lll b, lll c, lll d, lll x) {
    lll l = 127, r = (lll)1e10;
    while(l+1 < r) {
        lll mi = (l+r)/2;
        lll tmp = (a*mi*mi*mi+b*mi*mi+c*mi+d)/2;
        if(a) tmp /= 3;
        if(tmp == x) return 1;
        if(tmp < x) l = mi;
        else r = mi;
    }
    lll tmp = (a*l*l*l+b*l*l+c*l+d)/2;
    if(a) tmp /= 3;
    if(tmp == x) return 1;
    else return 0;
}

lll getncr(lll n, lll r) {
    lll ans = 1;
    for(lll i = 0; i < r; i++) ans = (n-i)*ans/(i+1);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tn = 127;
    vector<vector<lll>> P(tn+1), Q(tn+1);
    for(int i = 0; i < P.size(); i++) {
        for(int j = 0; j <= i; j++) {
            if(j == 0 || j == i) P[i].push_back(1);
            else P[i].push_back(P[i-1][j-1]+P[i-1][j]);
            if(j) Q[i].push_back(Q[i].back()+P[i].back());
            else Q[i].push_back(1);
        }
    }
    vector<lll> A; //P[n][r] : nCr, Q[n][r] = sigma k in 0 to r : nCk
    for(int i = 0; i < tn; i++) {
        for(int j = 0; j <= i; j++) {
            for(int k = i; k < tn; k++) {
                lll tmp =(Q[k+1][j+k-i]-P[k+1][j]+P[i][j]);
                if(j) tmp -= Q[k+1][j-1];
                A.push_back(tmp);
            }
        }
    }
    sort(A.begin(), A.end());
    vector<lll> C;
    for(int i = 3; i < 14; i++) {
        for(int j = 0; j <= i; j++) {
            for(int cnt = tn; ; cnt++) {
                lll tmp = 0;
                for(int y = 0; y <= j; y++)
                    for(int x = 0; x <= j-y; x++)
                        tmp += getncr(cnt-y, i+x-j);
                if(tmp >= LLIII) break;
                C.push_back(tmp);
            }
        }
    }
    sort(C.begin(), C.end());
    int t; cin >> t;
    while(t--) {
        ll n; cin >> n;
        if(n == 1LL) {
            cout << -1 << "\n";
        } else {
            ll ans = upper_bound(A.begin(), A.end(), (lll)n) - lower_bound(A.begin(), A.end(), (lll)n);
            ll cnt = (n >= tn) + (n >= (tn+2));
            cnt += binsea(0, 1, -1, 0, n) + binsea(0, 1, 3, -2, n) + binsea(0, 1, 3, 4, n);
            //cnt += binsea(1, -3, 2, 0, n) + binsea(1, 3, -10, 6, n) + binsea(1, 3, 8, -12, n) + binsea(1, 3, 8, 12, n);
            cnt += upper_bound(C.begin(), C.end(), (lll)n) - lower_bound(C.begin(), C.end(), (lll)n);
            cout << ans+2LL*cnt << "\n";
        }
    }
    return 0;
}