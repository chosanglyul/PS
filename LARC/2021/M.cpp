#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& arr) {
//    out << '[';
    for (int i=0; i<arr.size(); ++i) {
        out << arr[i];
        if (i+1 < arr.size()) out << ' ';
    }
//    out << ']';
    return out;
}

struct dat{
    ll d, t, ind;
    bool operator<(dat in){
        if(d-t==in.d-in.t)
            return t<in.t;
        return d-t<in.d-in.t;
    }
};
int N;
ll grace[6000], pre[6000];
dat input[6000];
int idx[6000], visited[6000];
vector <int> dap;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i=1;i<=N;i++){
        cin >> input[i].t >> input[i].d;
        input[i].ind = i;
    }
    sort(input+1, input+1+N);
    ll now = 0;
    for(int i=1;i<=N;i++){
        if(now>input[i].d-input[i].t){
            cout << "*";
            return 0;
        }
        grace[i] = input[i].d - input[i].t - now;
        now+=input[i].t;
        idx[input[i].ind]=i;
    }
    pre[1]=grace[1];
    for(int k=2;k<=N;k++)
        pre[k]=min(grace[k], pre[k-1]);
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++)if(!visited[j]&&pre[idx[j]-1]>=input[i].t){
            for(int k=1;k<idx[j];k++)
                grace[k]-=input[i].t;
            grace[idx[j]]=1e18;
            pre[1]=grace[1];
            for(int k=2;k<=N;k++)
                pre[k]=min(grace[k], pre[k-1]);
            visited[j]=1;
            dap.push_back(j);
            break;
        }
    }

    cout << dap;
    return 0;
}