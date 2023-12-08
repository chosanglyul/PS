#include <bits/stdc++.h>
using namespace std;
typedef pair<double, double> pdd;
#define fi first
#define se second

struct UF {
    private:
    vector<int> P;

    public:
    UF(int n) {
        P.resize(n);
        for(int i = 0; i < n; i++)
            P[i] = i;
    }

    int fin(int i) {
        if(P[i] == i) return i;
        return P[i] = fin(P[i]);
    }

    void mer(int i, int j) {
        i = fin(i), j = fin(j);
        if(i != j) P[i] = j;
    }
};

bool check(double r, double x, double y, vector<pdd> &A) {
    int n = A.size();
    UF uf(n+2);
    for(int i = 0; i < n; i++) {
        if(A[i].fi <= r || A[i].se >= y-r) uf.mer(i, n);
        if(A[i].se <= r || A[i].fi >= x-r) uf.mer(i, n+1);
        for(int j = 0; j < n; j++) {
            double dx = A[i].fi-A[j].fi, dy = A[i].se-A[j].se;
            if(dx*dx+dy*dy <= 4*r*r) uf.mer(i, j);
        }
    }
    return uf.fin(n) == uf.fin(n+1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y; cin >> x >> y;
    int n; cin >> n;
    vector<pdd> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    double l = 0.0, r = 1500000.0;
    for(int i = 0; i < 60; i++) {
        double m = (l+r)/2;
        if(check(m, x, y, A)) r = m;
        else l = m;
    }
    cout << fixed << setprecision(10) << l << "\n";
    return 0;
}