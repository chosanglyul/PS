#include <bits/stdc++.h>
#define fi first
#define se second
typedef long long ll;
using namespace std;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<pll, ll> plll;

struct uri{
    ll p, q;
};
uri gcdd(const uri a){
    ll g = __gcd(abs(a.p), abs(a.q));
    return {a.p/g, a.q/g};
}
struct line{
    uri a,b,c;
};
uri operator+(const uri a, const uri b){return gcdd({a.p*b.p,a.q*b.p+a.p*b.q});}
uri operator-(const uri a, const uri b){return gcdd({a.p*b.p,a.q*b.p-a.p*b.q});}
uri operator*(const uri a, const uri b){return gcdd({a.p*b.p, a.q*b.q});}
uri operator/(const uri a, const uri b){return gcdd({a.p*b.q, a.q*b.p});}
bool operator==(const uri a, const uri b){uri aa=gcdd(a), bb=gcdd(b);return (aa.p==bb.p&&aa.q==bb.q);}
bool operator<(const uri a, const uri b){return (a.q*b.p<a.p*b.q);}

struct gyopo{
    uri x, y;
    pii ha[2];
};
bool operator==(const gyopo a, const gyopo b){return a.x==b.x&&a.y==b.y;}
bool operator<(const gyopo a, const gyopo b){
    if(a.x==b.x)
        return a.y<b.y;
    return a.x<b.x;
}

ostream& operator<<(ostream& out, uri x) {
    out << gcdd(x).q << "/" << gcdd(x).p;
    return out;
}
ostream& operator<<(ostream& out, line now){
    cout << now.a << "x+(" << now.b << ")y+(" << now.c << ")=0\n";
    return out;
}
ostream& operator<<(ostream& out, gyopo now){
    out << now.x << ", " << now.y << "\n";
    out << "(" << now.ha[0].fi << "," << now.ha[0].se << ") ";
    out << "(" << now.ha[1].fi << "," << now.ha[1].se << ")\n";
    return out;
}

int n;
vector <pll> points;
vector <pii> linesup;
vector <line> lines;
vector <gyopo> mv;

vector <int> used;
int uni[50], unicnt;
int par(int now){if(now==uni[now])return now; return uni[now]=par(uni[now]);}
bool hap(int a, int b){
    used.push_back(a);
    used.push_back(b);
    a = par(a);
    b = par(b);
    if(a==b)
        return false;
    unicnt++;
    uni[b] = uni[a];
    return true;
}
bool hap(pii gg){return hap(gg.first, gg.second);}
void rest(){
    for(int now : used)
        uni[now]=now;
    used.clear();
    unicnt=0;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i=0;i<n;i++){
        ll xc, yc;
        cin >> xc >> yc;
        points.push_back(make_pair(xc, yc));
    }
    if(n==1){
        cout << "1\n";
        return 0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            pll p1 = points[i];
            pll p2 = points[j];
            linesup.push_back(make_pair(i, j));
            lines.push_back({{1ll,p2.fi-p1.fi}, {1ll, p2.se-p1.se},{2ll, 
                                p1.fi*p1.fi - p2.fi*p2.fi + p1.se*p1.se - p2.se*p2.se}});
//            cout << lines.back();
        }
    }
    for(int i=0;i<lines.size();i++){
        for(int j=0;j<i;j++){
            line l1 = lines[i];
            line l2 = lines[j];
            uri det = l1.a*l2.b-l2.a*l1.b;
            gyopo nowpo;
            nowpo.ha[0] = linesup[i];
            nowpo.ha[1] = linesup[j];
            if(det.q == 0){
                if(!(l1.a*l2.c == l2.a*l1.c && l1.b*l2.c == l2.b*l1.c))
                    continue;
                l1.c.q *=-1;
                if(l1.a.q==0){
                    nowpo.x = {1ll, 0ll};
                    nowpo.y = gcdd(l1.c/l1.b);
                }else{
                    nowpo.y = {1ll, 0ll};
                    nowpo.x = gcdd(l1.c/l1.a);
                }
                l1.c.q *= -1;
            }else{
                nowpo.x = gcdd((l2.c*l1.b-l1.c*l2.b)/det);
                nowpo.y = gcdd((l2.a*l1.c-l1.a*l2.c)/det);
            }
            mv.push_back(nowpo);
        }
    }
    if(mv.empty()){
        cout << n-1 << "\n";
        return 0;
    }
    sort(mv.begin(),mv.end());
    for(int i=1;i<=n;i++)
        uni[i]=i;

    vector <pll> gans;
    int dap = -1;
    gyopo zun = mv[0];
    for(gyopo now : mv){
        if(!(zun == now)){
            dap = min(dap, -unicnt);
            rest();
//            cout << "-----------------\n";
        }
//        cout << now;
        hap(now.ha[0]);
        hap(now.ha[1]);
        zun = now;
    }
    dap = min(dap, -unicnt);

    cout << n+dap << "\n";
    return 0;
}