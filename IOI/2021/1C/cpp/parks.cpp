#include "parks.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef pair<pi, int> pii;
#define fi first
#define se second

int cnt;
vector<int> S, RSCC, ans;
vector<pi> T, V;
vector<vector<int>> E, G, R, B, SCC, GE;
vector<bool> chk;

void dfs(int x) {
    if(chk[x]) return;
    chk[x] = true;
    for(auto i : E[x]) {
        if(chk[i]) continue;
        T.push_back({x, i});
        dfs(i);
    }
}

void dfs1(int x) {
    if(chk[x]) return;
    chk[x] = true;
    for(auto i : G[x]) dfs1(i);
    S.push_back(x);
}

void dfs2(int x) {
    if(chk[x]) return;
    chk[x] = true;
    SCC[cnt].push_back(x);
    RSCC[x] = cnt;
    for(auto i : R[x]) dfs2(i);
}

void topo() {
    vector<int> IN(GE.size(), 0);
    ans = vector<int>(G.size(), -1);
    for(auto &i : GE) for(auto j : i) IN[j]++;
    queue<pair<int, bool>> Q;
    for(auto i : IN) Q.push({i, false});
    while(Q.size()) {
        auto tmp = Q.front();
        Q.pop();
        for()
        for(auto i : GE[tmp.fi]) {
            if(--IN[i] == 0) Q.push({i, tmp.se});
        }

    }
}

void cg(vector<pii>& A) {
    sort(A.begin(), A.end());
    for(int i = 1; i < A.size(); i++) {
        if(A[i-1].fi.fi != A[i].fi.fi) continue;
        if(A[i-1].fi.se+2 == A[i].fi.se) {
            E[A[i-1].se].push_back(A[i].se);
            E[A[i].se].push_back(A[i-1].se);
        }
    }
}

int construct_roads(vector<int> x, vector<int> y) {
    vector<pii> A;
    for(int i = 0; i < x.size(); i++) A.push_back({{x[i], y[i]}, i});
    cg(A);
    for(auto &i : A) swap(i.fi.fi, i.fi.se);
    cg(A);
    for(auto &i : E) {
        sort(i.begin(), i.end());
        i.erase(unique(i.begin(), i.end()));
    }
    chk.resize(x.size());
    dfs(0);
    for(auto i : chk) if(!i) return 0;
    set<pi> VS;
    for(auto i : T) {
        pi c = {(x[i.fi]+x[i.se])/2, (y[i.fi]+y[i.se])/2};
        if(x[i.fi] == c.fi) {
            VS.insert({c.fi+1, c.se});
            VS.insert({c.fi-1, c.se});
        } else {
            VS.insert({c.fi, c.se+1});
            VS.insert({c.fi, c.se-1});
        }
    }
    for(auto &i : VS) V.push_back(i);
    for(int j = 0; j < T.size(); j++) {
        pi i = T[j];
        pi c = {(x[i.fi]+x[i.se])/2, (y[i.fi]+y[i.se])/2};
        if(x[i.fi] == c.fi) {
            B[lower_bound(V.begin(), V.end(), make_pair(c.fi+1, c.se))-V.begin()].push_back(j*2+1);
            B[lower_bound(V.begin(), V.end(), make_pair(c.fi-1, c.se))-V.begin()].push_back(j*2);
        } else {
            B[lower_bound(V.begin(), V.end(), make_pair(c.fi, c.se+1))-V.begin()].push_back(j*2+1);
            B[lower_bound(V.begin(), V.end(), make_pair(c.fi, c.se-1))-V.begin()].push_back(j*2);
        }
    }
    RSCC.resize(T.size()*4);
    G.resize(T.size()*4);
    for(int i = 0; i < T.size(); i++) {
        G[i*4+1].push_back(i*4+2);
        G[i*4+3].push_back(i*4);
    }
    for(auto &i : B) {
        for(auto &j : i) {
            for(auto &k : i) {
                if(j == k) continue;
                G[j*2].push_back(k*2+1);
                G[k*2].push_back(j*2+1);
            }
        }
    }
    for(int i = 0; i < G.size(); i++)
        for(auto j : G[i]) R[j].push_back(i);
    chk = vector<bool>(G.size(), false);
    for(int i = 0; i < chk.size(); i++) {
        if(!chk[i]) dfs1(i);
    }
    chk = vector<bool>(G.size(), false);
    for(int i = 0; i < chk.size(); i++) {
        int tmp = S.back();
        S.pop_back();
        if(!chk[tmp]) {
            dfs2(tmp);
            cnt++;
        }
    }
    for(int i = 0; i < RSCC.size()/2; i++) {
        if(RSCC[i<<1] == RSCC[i<<1|1]) return 0;
    }
    GE.resize(cnt);
    vector<set<int>> ge(cnt);
    for(int i = 0; i < G.size(); i++)
        for(auto j : G[i])
            if(RSCC[i] != RSCC[j])
                ge[RSCC[i]].insert(RSCC[j]);
    for(int i = 0; i < cnt; i++)
        for(auto j : ge[i])
            GE[i].push_back(j);
    dfs3(, false);
    return 1;
}
