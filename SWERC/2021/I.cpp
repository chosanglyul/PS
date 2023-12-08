#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

struct SEG{
    int N;
    int A[210000];
    set <pii> seg[808080];
    void build(int s, int e, int ind){
        seg[ind].clear();
        if(s==e){
            seg[ind].insert({A[s], s});
            return;
        }
        int m = (s+e)/2;
        build(s, m, ind*2);
        build(m+1, e, ind*2+1);
        for(auto i: seg[ind*2])
            seg[ind].insert(i);
        for(auto i: seg[ind*2+1])
            seg[ind].insert(i);
    }
    void findup(int s, int e, int ind, int x, int y, int th, vector <int> &v){
        if(s>=x && e<=y){
            for(auto it = seg[ind].lower_bound({th, 0});it!=seg[ind].end();it++)
                v.push_back((*it).se);
            return;
        }
        if(s>y||e<x)
            return;
        int m = (s+e)/2;
        findup(s, m, ind*2, x, y, th, v);
        findup(m+1, e, ind*2+1, x, y, th, v);
    }
    void finddown(int s, int e, int ind, int x, int y, int th, vector <int> &v){
        if(s>=x && e<=y){
            auto ed = seg[ind].upper_bound({th, N+1});
            for(auto it = seg[ind].begin();it!=ed;it++)
                v.push_back((*it).se);
            return;
        }
        if(s>y||e<x)
            return;
        int m = (s+e)/2;
        finddown(s, m, ind*2, x, y, th, v);
        finddown(m+1, e, ind*2+1, x, y, th, v);
    }
    void pop(int s, int e, int ind, int tr){
        if(s>tr || e<tr)
            return;
        seg[ind].erase({A[tr], tr});
        if(s<e){
            int m = (s+e)/2;
            pop(s, m, ind*2, tr);
            pop(m+1, e, ind*2+1, tr);
        }
    }
} ds[2];
int T;
int p[210000];
int ans[210000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while(T--){
        int n, a, b;
        cin >> n >> a >> b;
        for(int i=1;i<=n;i++)
            cin >> p[i];
        
        for(int i=1;i<=n;i++)
            ans[i] = 0;

        ds[0].N = ds[1].N = n;
        for(int i=1;i<=n;i++){
            ds[0].A[i] = i+p[i];
            ds[1].A[i] = i-p[i];
        }
        ds[0].build(1, n, 1);
        ds[1].build(1, n, 1);

        queue <int> mq;
        mq.push(a);
        ds[0].pop(1, n, 1, a);
        ds[1].pop(1, n, 1, a);
        while(!mq.empty()){
            int x = mq.front();
            vector <int> v;
            mq.pop();
            ds[0].findup(1, n, 1, x-p[x], x-1, x, v);
            ds[1].finddown(1, n, 1, x+1, x+p[x], x, v);
            for(int now : v){
                mq.push(now);
                ds[0].pop(1, n, 1, now);
                ds[1].pop(1, n, 1, now);
                ans[now] = ans[x]+1;
            }
        }
        cout << ans[b] << "\n";
    }

    return 0;
}