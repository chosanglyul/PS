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
struct card{
    int id;
    int C[3];
}input[110000];
int val[110000];
int n;
set <pii> M[3], V;
map <int, int> NM;
void update(int ind){
    if(V.find({val[ind], -input[ind].id}) != V.end())
        V.erase({val[ind], -input[ind].id});
    int nowval = 0;
    for(int col = 0; col<3; col++){
        auto now = M[col].find({input[ind].C[col], ind});
        auto nex = now, pre = now;
        nex++;
        if(nex == M[col].end())
            nex = M[col].begin();
        if(now == M[col].begin())
            pre = M[col].end();
        pre--;
        int nexang = (*nex).first;
        int preang = (*pre).first;
        int nowang = (*now).first;
        if(nowang == nexang || nowang == preang)
            continue;
        if(nexang > preang)
            nowval += nexang - preang;
        else
            nowval += nexang - preang + 360;
    }
    val[ind] = nowval;
    V.insert({val[ind], -input[ind].id});
}
void elim(int ind){
    vector<int> updateq;
    for(int col = 0; col<3; col++){
        auto now = M[col].find({input[ind].C[col], ind});
        auto nex = now, pre = now;
        nex++;
        if(nex == M[col].end())
            nex = M[col].begin();
        if(now == M[col].begin())
            pre = M[col].end();
        pre--;
        updateq.push_back((*nex).second);
        updateq.push_back((*pre).second);

        M[col].erase({input[ind].C[col], ind});
    }
    V.erase({val[ind], -input[ind].id});
    for(int x : updateq)
        update(x);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i=0;i<n;i++)
        cin >> input[i].C[0] >> input[i].C[1] >> input[i].C[2] >> input[i].id;

    for(int i=0;i<n;i++){
        for(int col=0;col<3;col++)
            M[col].insert({input[i].C[col], i});
        NM[input[i].id] = i;
    }
    for(int i=0;i<n;i++)
        update(i);

    for(int i=0;i<n-1;i++){
        auto now = V.begin();
        pii nowpii = *now;
        cout << -nowpii.second << "\n";
        elim(NM[-nowpii.second]);
    }
    cout << -(*(V.begin())).second << "\n";

    return 0;
}