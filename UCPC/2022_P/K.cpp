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

void dfs(int x, vector<int>& A, vector<int>& B, vector<vector<int>>& E) {
    //cout << " " << x << " " << E[x] << "\n";
    A[x] = E[x].size();
    if(E[x].empty()) return;
    vector<int> T(E[x].size(), -1);
    //cout << A[x] << " " << T;
    for(auto i : E[x]) {
        dfs(i, A, B, E);
        if(T.size() <= A[i]) {
            T.push_back(i);
            A[x]++;
        } else if(T[A[i]] != -1) {
            T[A[i]+1] = i;
            B.push_back(T[A[i]]);
            B.push_back(i);
        }
        else T[A[i]] = i;
    }
    for(auto i : T)
        if(i == -1)
            B.push_back(x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int m = 1<<n;
    vector<bool> chk(m, false);
    vector<vector<int>> E(m);
    for(int i = 2; i < m; i++) {
        int x, y; cin >> x >> y; --x, --y;
        E[x].push_back(y);
        chk[y] = true;
    }
    vector<int> A(m); //{valid, depth}
    vector<int> B; //invalid nodes
    int l = -1, r = -1;
    for(int i = 0; i < m; i++) {
        if(!chk[i]) {
            vector<int> T;
            dfs(i, A, T, E);
            //cout << T;
            if(T.empty()) {
                if(l == -1) l = i;
                else r = i;
            } else B = T;
        }
    }
    if(r == -1) {
        sort(B.begin(), B.end());
        for(auto i : B)
            cout << i+1 << " " << l+1 << "\n";
    } else {
        cout << l+1 << " " << r+1 << "\n";
        cout << r+1 << " " << l+1 << "\n";
    }
    return 0;
}