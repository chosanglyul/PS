#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
#define fi first
#define se second

void setA(vector<pii>& A, int idx, int L, int x) {
    idx += L;
    if(x < 0) A[idx].se = max(A[idx].se, -x);
    else A[idx].fi = max(A[idx].fi, x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll w, h, L; cin >> w >> h >> L;
    vector<pii> A(2*L+1, {0, 0});
    for(ll i = -L; i <= 0LL; i++) {
        int tmp = sqrt(L*L - i*i);
        setA(A, i, L, tmp);
        setA(A, i, L, -tmp);
        setA(A, -i, L, -tmp);
    }
    for(ll i = 0LL; i <= L-h; i++) {
        setA(A, i, L, sqrt((L-h)*(L-h) - i*i) + h);
    }
    for(ll i = w; i <= L; i++) {
        setA(A, i, L, sqrt((L-w)*(L-w) - (i-w)*(i-w)));
    }
    ll su = 0LL;
    for(int i = -L; i <= L; i++) {
        int idx = i+L;
        if(i < 0 || i > w) su += A[idx].fi+A[idx].se+1;
        else su += A[idx].se + max(0LL, A[idx].fi-h);
        //cout << A[idx].fi << " " << A[idx].se << " " << su << "\n";
    }
    cout << su << "\n";
    return 0;
}