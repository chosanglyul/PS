#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct sun{
    int e, c, d;
};
int n, m, k;
int s, t;
vector <sun> gan[1100];
vector <int> jap;
int vis[1100];
ll dap;
void dfs(int now, int ky){
    vis[now]=1;
    for(sun nex : gan[now])if(!vis[nex.e]&&nex.c<=ky&&nex.d>=ky)
        dfs(nex.e, ky);
}
bool chk(int ky){
    for(int i=1;i<=n;i++)
        vis[i]=0;
    dfs(s, ky);
    return vis[t];
}
void pluss(int st, int fin){
    if(st>fin)
        return;
    if(chk(st))
        dap += (fin-st+1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    cin >> s >> t;
    for(int i=0;i<m;i++){
        int u, v, c, d;
        cin >> u >> v >> c >> d;
        gan[u].push_back({v, c, d});
        jap.push_back(c);
        jap.push_back(d);
    }
    jap.push_back(1);
    jap.push_back(k);
    sort(jap.begin(), jap.end());
    jap.erase(unique(jap.begin(), jap.end()), jap.end());

    int zun = 1;
    for(int now : jap){
        pluss(zun, now-1);
        pluss(now, now);
        zun = now+1;
    }
    cout << dap << "\n";
    return 0;
}