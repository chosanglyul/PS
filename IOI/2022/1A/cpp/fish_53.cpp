#include "fish.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;

ll pre(int x, int s, int e, vvll &B) {
    if(x < 0 || x >= B.size()) return 0LL;
    return B[x][e] - B[x][s];
}

vll maxpre(int i, vvvll &D) {
    vll T(D[i-1].size(), 0LL);
    for(int j = 0; j < D[i-1].size(); j++)
        for(int k = 0; k <= j; k++)
            T[j] = max(T[j], D[i-1][j][k]);
    return T;
}

vll maxall(int i, vvvll &D) {
    vll T(D[i-1].size(), 0LL);
    for(int j = 0; j < D[i-1].size(); j++)
        for(int k = 0; k < D[i-1][j].size(); k++)
            T[j] = max(T[j], D[i-1][j][k]);
    return T;
}

ll max_weights(int N, int M, vector<int> X, vector<int> Y, vector<int> W) {
    bool subtask1 = true, subtask2 = true;
    for(auto i : X) {
        if(i%2) subtask1 = false;
        if(i >= 2) subtask2 = false;
    }
    if(subtask1) {
        ll ans = 0LL;
        for(auto i : W) ans += i;
        return ans;
    }
    if(subtask2) {
        vector<pll> A, B;
        for(int i = 0; i < M; i++) {
            if(X[i]) B.push_back({Y[i], W[i]});
            else A.push_back({Y[i], W[i]});
        }
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        if(N == 2) {
            ll a = 0LL, b = 0LL;
            for(auto &i : A) a += i.se;
            for(auto &i : B) b += i.se;
            return max(a, b);
        } else {
            ll tmp = 0LL;
            for(auto &i : B) tmp += i.se;
            B.push_back({N, 0});
            ll ans = tmp;
            for(int i = 0, j = 0; i < B.size(); i++) {
                while(j < A.size() && A[j].fi < B[i].fi) tmp += A[j++].se;
                ans = max(ans, tmp);
                tmp -= B[i].se;
            }
            return ans;
        }
    }

    int MX = min(N, 2+*max_element(X.begin(), X.end()));
    int MY = 2+*max_element(Y.begin(), Y.end());
    vvll A(MX, vll(MY, 0LL));
    for(int i = 0; i < M; i++) A[X[i]][Y[i]] += W[i];
    vvll B(MX, vll(MY, 0LL));
    for(int i = 0; i < MX; i++)
        for(int j = 1; j < MY; j++)
            B[i][j] = B[i][j-1]+A[i][j-1];

    vvvll D(MX, vvll(MY, vll(MY, 0LL)));
    for(int j = 0; j < MY; j++) {
        for(int k = 0; k < MY; k++) {
            if(j > k) D[1][j][k] = pre(2, 0, j, B)+pre(0, k, j, B);
            else D[1][j][k] = pre(2, 0, j, B)+pre(1, j, k, B);
        }
    }
    for(int i = 2; i < MX; i++) {
        vll MP = maxpre(i, D), MA = maxall(i, D);
        for(int j = 0; j < MY; j++) {
            for(int k = 0; k < MY; k++)
                D[i][j][0] = max(D[i][j][0], D[i-1][0][k]+pre(i-1, min(j, k), j, B)+pre(i+1, 0, j, B));
            for(int k = 1; k < MY; k++) {
                if(j > k) D[i][j][k] = MP[k]-pre(i, 0, k, B)+pre(i+1, 0, j, B)+pre(i-1, k, j, B);
                else D[i][j][k] = MA[k]-pre(i, 0, j, B)+pre(i+1, 0, j, B);
            }
        }
    }
    //cout << " " << D;
    
    ll ans = 0LL;
    for(int i = 0; i < MY; i++)
        for(int j = 0; j < MY; j++)
            ans = max(ans, D.back()[i][j]);
    return ans;
}
