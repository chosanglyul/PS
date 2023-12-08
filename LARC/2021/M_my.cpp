#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, pair<int, int>> pii;
const int INF = (int)1e9+5;
#define fi first
#define se second

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& arr) {
    out << '[';
    for (int i=0; i<arr.size(); ++i) {
        out << arr[i];
        if (i+1 < arr.size()) out << ' ';
    }
    out << ']';
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pii> A(n);
    for(int i = 0; i < n; i++) {
        A[i].se.fi = i;
        cin >> A[i].se.se >> A[i].fi;
    }
    sort(A.begin(), A.end());
    ll tmp = 0LL;
    for(int i = 0; i < n; i++) {
        tmp += A[i].se.se;
        if(tmp > A[i].fi) {
            cout << "*\n";
            return 0;
        }
    }
    for(int i = 0; i < n; i++) {
        vector<pii> T(A);
        vector<int> S(n);
        S[0] = T[0].se.se;
        for(int j = 1; j < n; j++) S[j] = S[j-1]+T[j].se.se;
        int mi = INF, idx = i;
        for(int j = i; j < n; j++) {
            if(mi >= T[j].se.se && T[idx].se.fi > T[j].se.fi) idx = j;
            mi = min(mi, T[j].fi - S[j]);
        }
        pii tt = T[idx];
        for(int j = idx; j > i; j--) T[j] = T[j-1];
        T[i] = tt;
        A = T;
    }
    for(auto &i : A) cout << i.se.fi+1 << " ";
    cout << "\n";
    return 0;
}