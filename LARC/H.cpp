#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

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
struct MCMFGraph{
    struct Edge{
        int from, to;
        ll c, f, cost;
        Edge *dual;
    };
    vector <ll> dist;
    vector <bool> InQ;
    vector <Edge*> bt;
    vector <vector<Edge*>> G;

    MCMFGraph(int n){
        G.resize(n+1); InQ.resize(n+1);
        dist.resize(n+1); bt.resize(n+1);
    }
    void add_edge(int u, int v, int c, ll cost){
        Edge *e1 = new Edge {u, v, c, 0, cost, nullptr};
        Edge *e2 = new Edge {v, u, 0, 0, -cost, nullptr};
        e1->dual = e2; e2->dual = e1;
        G[u].push_back(e1); G[v].push_back(e2);
    }
    pii solve(int src, int snk){
        ll total_cost=0, total_flow=0;
        while(1){
            fill(dist.begin(), dist.end(), 1e18);
            fill(bt.begin(), bt.end(), nullptr);
            fill(InQ.begin(), InQ.end(), 0);

            queue <int> Q;
            dist[src]=0;
            Q.push(src); InQ[src]=1;
            while(!Q.empty()){
                int x=Q.front(); Q.pop();
                InQ[x] = 0;

                for(Edge *e : G[x]){
                    if(e->c == e->f) continue;
                    if(dist[e->to]>dist[x]+e->cost){
                        dist[e->to] = dist[x]+e->cost;
                        bt[e->to] = e;
                        if(!InQ[e->to]){
                            Q.push(e->to); InQ[e->to]=1;
                        }
                    }
                }
            }
            if(dist[snk]==1e18)break;
            ll x=0, f=1e18;
            for(auto e = bt[snk]; e; e=bt[e->from]){
                f = min(f, e->c - e->f);
            }
            for(auto e=bt[snk];e;e=bt[e->from]){
                e->f += f;
                e->dual->f -= f;
                total_cost += f*e->cost;
            }
            total_flow += f;
        }
        return {total_flow, total_cost};
    }
}*M;
int N;
ll L[600][600];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++)
            cin >> L[i][j];
    }
    M = new MCMFGraph(N+2);
    for(int i=2;i<=N+1;i+=2){
        for(int j=1;j<=N;j+=2)
            M->add_edge(i, j, 1, L[i][j]+L[i-2][j]);
    }
    for(int i=1;i<=N;i+=2)
        M->add_edge(i, N+2, 1, 0ll);
    for(int i=2;i<=N+1;i+=2)
        M->add_edge(0, i, 1, 0ll);
    pii dap = M->solve(0, N+2);
    cout << dap.second;
    return 0;
}