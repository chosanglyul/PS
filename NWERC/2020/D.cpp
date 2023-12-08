#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAX = 1'000'000LL;
typedef pair<ll, ll> pll;
#define fi first
#define se second

vector<pll> solve(ll xx, ll yy) {
    cout << xx << " " << yy << "\n"; cout.flush();
    ll d; cin >> d;
    if(d == 0LL) return {{xx, yy}};
    vector<pll> ans;
    for(ll x = MAX, y = 0LL; x >= 0LL; x--) {
        while(x*x+y*y < d) y++;
        if(y > MAX) break;
        if(x*x+y*y == d) {
            pll tmp;
            if(xx == MAX) tmp.fi = xx-x;
            else tmp.fi = x;
            if(yy == MAX) tmp.se = yy-y;
            else tmp.se = y;
            ans.push_back(tmp);
        }
    }
    return ans;
}

void query(vector<pll> &A) {
    for(auto &i : A) {
        cout << i.fi << " " << i.se << "\n"; cout.flush();
        ll d; cin >> d;
        if(d == 0LL) return;
    }
}

int main() {
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        vector<vector<pll>> A;
        A.push_back(solve(0LL, 0LL));
        if(A.back() == vector<pll>(1, {0LL, 0LL})) continue;
        A.push_back(solve(0LL, MAX));
        if(A.back() == vector<pll>(1, {0LL, MAX})) continue;
        A.push_back(solve(MAX, 0LL));
        if(A.back() == vector<pll>(1, {MAX, 0LL})) continue;
        A.push_back(solve(MAX, MAX));
        if(A.back() == vector<pll>(1, {MAX, MAX})) continue;
        int mi = MAX;
        for(int i = 0; i < A.size(); i++)
            if(mi > A[i].size()) mi = A[i].size();
        for(int i = 0; i < A.size(); i++)
            if(mi == A[i].size()) {
                query(A[i]);
                break;
            }
    }
    return 0;
}
