#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
pii operator+(pii in1, pii in2){
    return {in1.fi+in2.fi,in1.se+in2.se};
}
pii operator-(pii in1, pii in2){
    return {in1.fi-in2.fi,in1.se-in2.se};
}
mt19937 rng(1010101);
ll randInt(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}
pii randPair(ll l, ll r){
    return {randInt(l, r), randInt(l, r)};
}
const int RANDNUM=100;

int n;
int tbl[5010][5010];
pii a, b;
set <pii> ms;
vector <pii> moves;
bool chk(pii now){
    return now.fi>0&&now.fi<=n&&now.se>0&&now.se<=n;
}
bool dest(pii s, pii e){
    for(pii now : moves) if(s == e || now + s == e || (chk(now+s) && ms.find(e-s-now)!=ms.end()))
        return true;
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    cin >> a.fi >> a.se;
    cin >> b.fi >> b.se;
    moves.resize(n);
    for(int i=0;i<n;i++)
        cin >> moves[i].fi >> moves[i].se;#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
pii operator+(pii in1, pii in2){
    return {in1.fi+in2.fi,in1.se+in2.se};
}
pii operator-(pii in1, pii in2){
    return {in1.fi-in2.fi,in1.se-in2.se};
}
mt19937 rng(1010101);
ll randInt(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}
pii randPair(ll l, ll r){
    return {randInt(l, r), randInt(l, r)};
}
const int RANDNUM=100;

int n;
int tbl[5010][5010];
pii a, b;
set <pii> ms;
vector <pii> moves;
bool chk(pii now){
    return now.fi>0&&now.fi<=n&&now.se>0&&now.se<=n;
}
bool dest(pii s, pii e){
    for(pii now : moves) if(s == e || now + s == e || (chk(now+s) && ms.find(e-s-now)!=ms.end()))
        return true;
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    cin >> a.fi >> a.se;
    cin >> b.fi >> b.se;
    moves.resize(n);
    for(int i=0;i<n;i++)
        cin >> moves[i].fi >> moves[i].se;
    for(pii now : moves)
        ms.insert(now);
    
    if(dest(a, b)){
        cout << "Alice wins\n";
        return 0;
    }

    if(n <= 5000){
        vector <pii> mv;
        tbl[b.fi][b.se]=1;
        for(pii now : moves) if(chk(now+b))
            mv.push_back(now+b);
        for(pii now : mv){
            tbl[now.fi][now.se]=1;
            for(pii move : moves) if(chk(now+move))
                tbl[(now+move).fi][(now+move).se]=1;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) if(!tbl[i][j]){
                cout << "tie " << i << " " << j << "\n";
                return 0;
            }
        }
    }
    else{
        for(int t = 0;t<RANDNUM;t++){
            pii e = randPair(1, n);
            if(!dest(b, e)){
                cout << "tie " << e.fi << " " << e.se << "\n";
                return 0;
            }
        }
    }
    
    cout << "Bob wins\n";
    return 0;
}
    for(pii now : moves)
        ms.insert(now);
    
    if(dest(a, b)){
        cout << "Alice wins\n";
        return 0;
    }

    if(n <= 5000){
        vector <pii> mv;
        tbl[b.fi][b.se]=1;
        for(pii now : moves) if(chk(now+b))
            mv.push_back(now+b);
        for(pii now : mv){
            tbl[now.fi][now.se]=1;
            for(pii move : moves) if(chk(now+move))
                tbl[(now+move).fi][(now+move).se]=1;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) if(!tbl[i][j]){
                cout << "tie " << i << " " << j << "\n";
                return 0;
            }
        }
    }
    else{
        for(int t = 0;t<RANDNUM;t++){
            pii e = randPair(1, n);
            if(!dest(b, e)){
                cout << "tie " << e.fi << " " << e.se << "\n";
                return 0;
            }
        }
    }
    
    cout << "Bob wins\n";
    return 0;
}