#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int x0, y0, xt, yt; cin >> x0 >> y0 >> xt >> yt;
    vector<pii> A(n);
    for(int i = 0; i < n; i++) cin >> A[i].fi >> A[i].se;
    vector<string> ans;
    while(x0 >= 0) {
        ans.push_back("left");
        x0--;
    }
    ans.push_back("up");
    for(int i = 0; i < 35; i++) ans.push_back("left");
    ans.push_back("down");
    for(int i = 0; i < 35; i++) ans.push_back("right");
    while(y0 > 0) {
        ans.push_back("down");
        y0--;
    }
    for(int i = 0; i < 31; i++) {
        int tmp = x0;
        while(tmp < xt) {
            tmp++;
            ans.push_back("right");
        }
        while(tmp > x0) {
            tmp--;
            ans.push_back("left");
        }
        y0++;
        ans.push_back("up");
    }
    for(int i = 0; i < 31; i++) {
        y0--;
        ans.push_back("down");
    }
    y0--;
    ans.push_back("down");
    while(x0 < xt) {
        x0++;
        ans.push_back("right");
    }
    for(int i = 0; i < 31; i++) {
        int tmp = y0;
        while(tmp < yt) {
            tmp++;
            ans.push_back("up");
        }
        while(tmp > y0) {
            tmp--;
            ans.push_back("down");
        }
        x0++;
        ans.push_back("right");
    }
    while(y0 < yt) {
        y0++;
        ans.push_back("up");
    }
    for(int i = 0; i < 32; i++) {
        int tmp = x0;
        while(tmp > xt) {
            tmp--;
            ans.push_back("left");
        }
        while(tmp < x0) {
            tmp++;
            ans.push_back("right");
        }
        for(int j = 0; j < 31-i; j++) {
            y0++;
            ans.push_back("up");
        }
        while(tmp > xt) {
            tmp--;
            ans.push_back("left");
        }
        while(tmp < x0) {
            ans.push_back("down");
            ans.push_back("up");
            tmp++;
            ans.push_back("right");
        }
        for(int j = 0; j < 31-i; j++) {
            y0--;
            ans.push_back("down");
        }
    }
    for(auto i : ans) cout << i << "\n";
    return 0;
}