#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
#define fi first
#define se second
const int INF = 1e9+5;
const int P = 1000000007;
const ll LLINF = (ll)1e18+5;
int n,m;
ll opt[3000][3000];
int vis[3000][3000];
vector <pil> gan[3000];
vector <int> daps;
int chk[3000];
queue <pii> mq;
bool operator<(pll a, pll b){
    return (__int128_t)a.fi*b.se > (__int128_t)b.fi * a.se;
}
pll get_p(int ind){return {ind, opt[n][ind]};}
pll gyo(pll a, pll b){return {a.fi-b.fi, b.se-a.se};}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v;
        ll w;
        cin >> u >> v >> w;
        gan[u].push_back({v, w});
        gan[v].push_back({u, w}); 
    }
    opt[1][0]=1;
    for(int y=0;y<n;y++){
        for(int u = 1;u<=n;u++)if(opt[u][y]){
            ll w =opt[u][y];
            for(pil nex : gan[u])if(!opt[nex.fi][y+1]||opt[nex.fi][y+1]>=opt[u][y]+nex.se){
                opt[nex.fi][y+1]=opt[u][y]+nex.se;
            }
        }
    }
 
    int ind = n-1;
    for(int i=n-1;i>0;i--)if(opt[n][i]&&opt[n][i]<opt[n][ind])
        ind = i;

    for(int i=0;i<n;i++) if(opt[n][i]==opt[n][ind])
        mq.push({n, i});
    daps.push_back(ind);
    for(int i=ind-1;i>0;i--) if(opt[n][i]){
        while(daps.size()>1){
            pll bp = get_p(daps.back());
            pll ap = get_p(daps[daps.size()-2]);
            pll ip = get_p(i);
            if(gyo(ap, ip)<gyo(ap, bp))
                daps.pop_back();
            else
                break;
        }
        daps.push_back(i);
    }
 
    for(int y : daps)
        mq.push({n, y});
    while(!mq.empty()){
        int x = mq.front().fi;
        int y = mq.front().se;
        mq.pop();
        chk[x]=1;
        vis[x][y]=1;
        for(pil nex : gan[x])if(opt[nex.fi][y-1]&&!vis[nex.fi][y-1]&&opt[nex.fi][y-1]+nex.se==opt[x][y]){
            chk[nex.fi]=1;
            vis[nex.fi][y-1]=1;
            mq.push({nex.fi, y-1});
        }
    }
    int cnt=0;
    for(int i=1;i<=n;i++)
        cnt+=1-chk[i];
    cout << cnt << "\n";
    for(int i=1;i<=n;i++)if(!chk[i])
        cout << i << " ";
 
    return 0;
}