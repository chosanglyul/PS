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
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

int mod(int a, int b) { return ((a%b) + b) % b; }

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<pi> A(n);
    for(int i = 0; i < n; i++) {
        cin >> A[i].fi;
        A[i].se = i+1;
    }
    while(A.size() > 1) {
        int nn = A.size();
        int tmp = m%nn;
        int st = mod(tmp-1, nn);
        int k = st;
        //cout << nn << " " << tmp << "\n";
        pi mi = {INF, INF};
        do {
            if(mi.fi > A[k].fi) mi = {A[k].fi, k};
            //cout << k << " ";
            k = (k+tmp)%nn;
        } while(k != st);
        //cout << "   " << mi << "\n";
        k = st;
        bool addi = true;
        do {
            A[k].fi -= mi.fi;
            if(!addi) A[k].fi++;
            if(k == mi.se) addi = false;
            k = (k+tmp)%nn;
        } while(k != st);
        vector<pi> B;
        for(int j = 1; j < nn; j++)
            if(A[(mi.se+j)%nn].fi)
                B.push_back(A[(mi.se+j)%nn]);
        A = B;
        //cout << A;
    }
    cout << A[0].se << "\n";
    return 0;
}