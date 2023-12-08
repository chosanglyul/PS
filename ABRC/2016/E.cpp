#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

class HLD{
    public:
        vector<vector<int>> adj;
        vector<int> in, sz, par, top, depth;
        int n=0;
        void traverse1(int u){
            sz[u]=1;
            for(int &v:adj[u]){
                adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
                depth[v] = depth[u]+1;
                traverse1(v);
                par[v] = u;
                sz[u] += sz[v];
                if(sz[v]>sz[adj[u][0]]) swap(v, adj[u][0]);
            }
        }
        void traverse2(int u){
            in[u] = n++;
            for(int v:adj[u]){
                top[v] = (v==adj[u][0]?top[u]:v);
                traverse2(v);
            }
        }
        void link(int u, int v){
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        void init(){
            top[1] = 1;
            traverse1(1);
            traverse2(1);
        }
        pii subtree(int u){
            return {in[u], in[u]+sz[u]};
        }
        vector<pii> path(int u, int v){
            vector<pii> res;
            while(top[u]!=top[v]){
                if(depth[top[u]]<depth[top[v]]) swap(u, v);
                res.emplace_back(in[top[u]], in[u]+1);
                u = par[top[u]];
            }
            res.emplace_back(min(in[u], in[v]), max(in[u], in[v])+1);
            return res;
        }
        HLD(int n){
            adj.resize(n+1); depth.resize(n+1);
            in.resize(n+1); sz.resize(n+1);
            par.resize(n+1); top.resize(n+1);
        }
};
struct query{
    int m,ind,u,v,siz,key;
    int l=0, r=100000;
    bool islow=true;
    bool operator<(query in){
        return m<in.m;
    }
};
ostream& operator<<(ostream& os, const query now){
    os << "l: " << now.l << ", r: " << now.r << ", m: " << now.m << ", u: " << now.u << ", v: " << now.v << ", key: " << now.key << "islow: " << now.islow<<"\n";
    return os;
}
int fen[110000];
int T, N, Q;
void clear(){for(int i=0;i<=N;i++)fen[i]=0;}
int sum(int ind){ll re=0;for(;ind>0;ind-=(ind&-ind))re+=fen[ind]; return re;}
void update(int ind){for(;ind<=N;ind+=(ind&-ind))fen[ind]++;}
void fuckingjudge(int a){
    if(a&1)
        cout << a/2 << ".5\n";
    else
        cout << a/2 << ".0\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while(T--){
        cin >> N;
        HLD hld(N);
        vector <piii> gans(N);
        clear();
        for(int i=1;i<N;i++){
            cin >> gans[i].se.fi >> gans[i].se.se >> gans[i].fi;
            hld.link(gans[i].se.fi, gans[i].se.se);
        }
        hld.init();
        vector <pii> gap;
        for(int i=1;i<N;i++){
            if(hld.par[gans[i].se.se] == gans[i].se.fi)
                gap.emplace_back(gans[i].fi, gans[i].se.se);
            else
                gap.emplace_back(gans[i].fi, gans[i].se.fi);
        }
        sort(gap.begin(), gap.end());
        cin >> Q;
        vector <query> qurs;
        vector <pii> dap(Q, {0,0});
        for(int i=0;i<Q;i++){
            query now;
            cin >> now.u >> now.v;
            vector <pii> nowpath = hld.path(now.u, now.v);
            now.siz = 0;
            for(pii pat : nowpath)
                now.siz += pat.se-pat.fi;
            now.siz--;

            now.ind = i;
            if(now.siz&1){
                now.key = now.siz/2+1;
                qurs.push_back(now);
            }
            else{
                now.key = now.siz/2;
                qurs.push_back(now);
                now.islow = false;
                now.key = now.siz/2+1;
                qurs.push_back(now);
            }
        }

        while(true){
            bool flg = true;
            for(query &now : qurs)if(now.l<=now.r){
                now.m = (now.l+now.r)/2;
                flg = false;
            }
            if(flg)
                break;
            sort(qurs.begin(), qurs.end());
            clear();
            int ind=0;
            for(query &now : qurs)if(now.l<=now.r){
                while(ind<gap.size()&&gap[ind].fi<=now.m){
                    update(hld.in[gap[ind].se]+1);
//                    cout << "update :" << hld.in[gap[ind].se]+1 << "\n";
                    ind++;
                }
                int siz1=0;
                vector <pii> nowpath = hld.path(now.u, now.v);
                for(pii pat : nowpath){
                    siz1 += sum(pat.se)- sum(pat.fi);
//                    cout << pat.fi << ", " << pat.se << "\n";
                }
                int lca = nowpath.back().fi;
                siz1 -= sum(lca+1)-sum(lca);
                if(siz1 >= now.key)
                    now.r = now.m-1;
                else
                    now.l = now.m+1;

//                cout << now << siz1 << "\n";
            }
        }
        for(query now: qurs){
//            cout << now.islow << "tt" << now.ind << "tt" << now.l << "\n";
            if(now.islow)
                dap[now.ind].fi = now.l;
            else
                dap[now.ind].se = now.l;
        }
        for(pii tmp: dap){
//            cout <<tmp.fi << " kk " << tmp.se << "\n";
            if(tmp.se)
                fuckingjudge(tmp.fi + tmp.se);
            else
                fuckingjudge(tmp.fi * 2);
        }
    }

    return 0;
}