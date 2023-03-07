#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second

vector<int> make_query(int x, int y, vector<pii> &que, vector<int> &A) {
    que.push_back({x, y});
    vector<int> T;
    for(int i = y; i < A.size(); i++) T.push_back(A[i]);
    for(int i = x; i < y; i++) T.push_back(A[i]);
    for(int i = 0; i < x; i++) T.push_back(A[i]);
    //cout << x << " " << y << "\n";
    //for(auto i : T) cout << i << " ";
    //cout << "\n";
    return T;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<pii> que;
    while(true) {
        vector<pii> seg;
        for(int r = 1, l = 0; r <= n; r++) {
            if(r == n || A[r]-1 != A[r-1]) {
                seg.push_back({l, r});
                l = r;
            }
        }
        //for(auto i : seg) cout << i.fi << " " << i.se << "   ";
        //cout << "\n";
        if(seg.size() == 1) break;
        sort(seg.begin(), seg.end(), [&](pii &a, pii &b) {
            return A[a.fi] < A[b.fi];
        });
        bool can = false;
        for(int i = 1; i < seg.size(); i++) {
            if(!can && seg[i].fi == 0) {
                A = make_query(seg[i].se, seg[i-1].se, que, A);
                can = true;
            }
        }
        for(int i = 0; i+1 < seg.size(); i++) {
            if(!can && seg[i].se == n) {
                A = make_query(seg[i+1].fi, seg[i].fi, que, A);
                can = true;
            }
        }
        if(!can) A = make_query(seg[0].se, seg[0].se, que, A);
    }
    if(que.size() >= n) {
        cout << -1 << "\n";
        return 0;
    }
    reverse(que.begin(), que.end());
    cout << que.size() << "\n";
    for(auto i : que) {
        if(i.fi == i.se) cout << "2 " << n-i.fi << "\n";
        else if(i.fi == 0) cout << "2 " << n-i.se << "\n";
        else if(i.se == n) cout << "2 " << n-i.fi << "\n";
        else cout << "3 " << n-i.se << " " << n-i.fi << "\n";
    }
    return 0;
}