#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second

template<typename T, typename S>
std::ostream& operator<<(std::ostream& out, const std::pair<T, S>& p) {
    out << '(' << p.first << ' ' << p.second << ')';
    return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    out << '[';
    for (int i=0; i<(int)v.size(); ++i) {
        out << v[i];
        if (i != (int)v.size()-1) out << ' ';
    }
    out << ']';
    return out;
}

#define print(...) showi(cout, #__VA_ARGS__, __VA_ARGS__)

template<typename H1>
std::ostream& show(std::ostream& out, const char* label, H1&& value) {
    return out << label << " = " << value << std::endl;
}

template<typename H1, typename ...T>
std::ostream& show(std::ostream& out, const char* label, H1&& value, T**... rest) {
    const char* first_comma = strchr(label, ',');
    const char* left_paren = strchr(label, '(');
    if (left_paren != nullptr && left_paren < first_comma) {
        const char* right_paren = strchr(left_paren, ')');
        assert(right_paren != nullptr);
        const char* pcomma = strchr(right_paren, ')');
        return show(out.write(label, pcomma - label) << " = " << value << ',', pcomma+1, rest...);
    }
    return show(out.write(label, first_comma - label) << " = " << value << ',', first_comma+1, rest...);
}
template <typename T>
std::ostream& operator <<(std::ostream& out, const std::set<T>& s){
    out << '{';
    for (T x: s){
        out << x << ' ';
    }
    out << '}' << '\n';
    return out;
}
struct dat{
    int l,r,ind;
    ll c;

}input[500000];
std::ostream& operator <<(std::ostream& out, const dat& s){
    out << '[';
    out << s.l << ' ' << s.r << ' ' << s.ind << ' ' << s.c;
    out << ']' << '\n';
    return out;
}
bool operator<(dat a, dat b){
    if(a.l==b.l)
        return a.r<b.r;
    return a.l<b.l;
}
set <dat> querys;
int n,q;
ll sum[500000],sum2[500000];
ll mod = 998244353LL;
ll md(ll x) { return ((x%mod)+mod)%mod; }
ll cal(ll s, ll e, ll l, ll r, ll c){
    c = md(c);
    ll re = md((e-s)*(r-l+1LL));
    re = md(md(re*s)*c);
    ll a = md(((ll)n+1LL)*md(sum[r]-sum[l-1]));
    ll b = md(sum2[r]-sum2[l-1]);
    re = md(re*md(a-b));
    cout << a << ' ' << b << "\n";
    cout << l << ' ' << r << ' ' << s << ' ' << e << ' ' << c << ' ' << re << '\n';
    return re;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll dap=0;

    cin >> n >> q;
    for(int i=1;i<=q;i++){
        cin >> input[i].l >> input[i].r >>input[i].c;
        input[i].ind=i;
    }
    input[q+1]={1,n,q+1,0LL};
    q++;
    // TODO
    for(int i=1;i<=n;i++)
        sum[i]=i;
    for(int i=1;i<=n;i++)
        sum[i]=md(sum[i]+sum[i-1]);
    for(int i=1;i<=n;i++)
        sum2[i]=md((ll)i*i);
    for(int i=1;i<=n;i++)
        sum2[i]=md(sum2[i]+sum2[i-1]);
    querys.insert({1,n,0,0ll});
    for(int i=1;i<=q;i++){
        auto it = querys.lower_bound(input[i]);
        dat t1, t2;
        bool s1=0, s2=0;
        if(it!=querys.begin()){
            it--;
            if((*it).r>input[i].r){
                dap = md(dap+cal((*it).ind, i, input[i].l, input[i].r, (*it).c));
                dat now = (*it);
                querys.erase(it);
                dat nowl = now;
                nowl.r = input[i].l-1;
                querys.insert(nowl);
                now.l = input[i].r+1;
                querys.insert(now);
                continue;
            }
            if((*it).r>=input[i].l){
                s1=1;
                t1=(*it);
                dap = md(dap+cal((*it).ind,i,input[i].l,(*it).r,(*it).c));
            }
            it++;
        }
        auto st = it;
        while(it!=querys.end()&&(*it).r<=input[i].r){
            dap = md(dap+cal((*it).ind,i,(*it).l,(*it).r,(*it).c));
            it++;
        }
        auto fin = it;
        if(it!=querys.end()&&(*it).l<=input[i].r){
            s2=1;
            t2=(*it);
            dap = md(dap+cal((*it).ind,i,(*it).l,input[i].r,(*it).c));
        }
        querys.erase(st,fin);
        if(s1){
            querys.erase(t1);
            t1.r = input[i].l-1;
        }
        if(s2){
            querys.erase(t2);
            t2.l = input[i].r+1;
            querys.insert(t2);
        }
        if(s1){
            querys.insert(t1);
        }
        querys.insert(input[i]);
        cout << querys;
    }
    cout << md(dap) << "\n";
    return 0;
}