#include "parks.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef pair<pi, pi> pii;
#define fi first
#define se second

vector<int> p;

int fin(int i) {
    if(i == p[i]) return i;
    return p[i] = fin(p[i]);
}

void mer(int i, int j) {
    i = fin(i), j = fin(j);
    p[i] = j;
}

int construct_roads(vector<int> x, vector<int> y) {
    p.resize(x.size());
    for(int i = 0; i < x.size(); i++) p[i] = i;
    vector<vector<pi>> A(3);
    for(int i = 0; i < x.size(); i++)
        A[(x[i]>>1)-1].push_back({y[i], i});
    for(auto &i : A) sort(i.begin(), i.end());
    vector<pii> E;

    for(int i = 1; i < A[0].size(); i++) {
        if(A[0][i-1].fi+2 == A[0][i].fi) {
            E.push_back({{A[0][i-1].se, A[0][i].se}, {1, A[0][i-1].fi+1}});
            mer(A[0][i-1].se, A[0][i].se);
        }
    }
    for(int i = 1; i < A[2].size(); i++) {
        if(A[2][i-1].fi+2 == A[2][i].fi) {
            E.push_back({{A[2][i-1].se, A[2][i].se}, {7, A[2][i-1].fi+1}});
            mer(A[2][i-1].se, A[2][i].se);
        }
    }

    vector<bool> chk(404040, false);
    for(int i = 0, j = 0, k = 0; j < A[1].size(); j++) {
        while(i < A[0].size() && A[0][i].fi < A[1][j].fi) i++;
        if(i < A[0].size() && A[0][i].fi == A[1][j].fi && !(fin(A[0][i].se) == fin(A[1][j].se))) {
            E.push_back({{A[0][i].se, A[1][j].se}, {3, A[0][i].fi+1}});
            chk[A[0][i].fi+1] = true;
            mer(A[0][i].se, A[1][j].se);
        }
        while(k < A[2].size() && A[2][k].fi < A[1][j].fi) k++;
        if(k < A[2].size() && A[2][k].fi == A[1][j].fi && !(fin(A[2][k].se) == fin(A[1][j].se))) {
            E.push_back({{A[2][k].se, A[1][j].se}, {5, A[2][k].fi-1}});
            mer(A[2][k].se, A[1][j].se);
        }
    }

    for(int i = 1; i < A[1].size(); i++) {
        if(A[1][i-1].fi+2 == A[1][i].fi && !(fin(A[1][i-1].se) == fin(A[1][i].se))) {
            pi l;
            if(!chk[A[1][i-1].fi+1]) l = {3, A[1][i-1].fi+1};
            else l = {5, A[1][i-1].fi+1};
            E.push_back({{A[1][i-1].se, A[1][i].se}, l});
            mer(A[1][i-1].se, A[1][i].se);
        }
    }
    for(int i = 0; i < x.size(); i++) {
        if(fin(i) != fin(0)) return 0;
    }
    vector<int> a, b, c, d;
    for(auto &i : E) {
        a.push_back(i.fi.fi);
        b.push_back(i.fi.se);
        c.push_back(i.se.fi);
        d.push_back(i.se.se);
    }
    build(a, b, c, d);
    return 1;
}
