#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second

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
int n,m;
int A[500000],B[500000],a[500000],b[500000], c[500000], chk[1000000];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    for(int i=1;i<=n;i++)
        cin >> A[i];
    for(int i=1;i<=n;i++)
        cin >> B[i];

    if(n==m){
        cout << "-1";
        return 0;
    }

    for(int i=1;i<=n;i++)if(A[i]){
        a[A[i]]=i;
    }
    for(int i=1;i<=n;i++){
        if(b[B[i]]){
            cout << "-1";
            return 0;
        }
        b[B[i]]=i;
    }
    for(int i=1;i<=m;i++)if(a[i])
        c[i]=B[a[i]];
    
    int mind = 1;
    for(int i=1;i<=m;i++)if(c[mind]>c[i])
        mind=i;
    for(int i=mind;i!=mind;i=(i+1)%m){
        if(i==0)
            continue;
        if(c[(i+1)%m]<c[i]){
            cout << "-1";
            return 0;
        }
    }
    
    ll dap = 0;
    int snum =0;

    for(int i=1;i<=m;i++)if(a[i]){
        dap +=(i-c[i]+m)%m;
        chk[c[i]]+=1;
        if(c[i]>i)
            chk[i+m+1]-=1;
        else if(c[i]==i)
            snum++;
        else
            chk[i+1]-=1;
    }
    for(int i=1;i<=2*m;i++)
        chk[i]+=chk[i-1];
    int s =0;
    for(int i=1;i<=m;i++)if(a[i]&&i==c[i]&&chk[i]){
        s=1;
        break;
    }
    if(s)
        dap+=(ll)m*snum;
    cout << dap;
    return 0;
}