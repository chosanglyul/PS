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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> L(1010101), R(1010101);
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        L[x].push_back(y);
        R[y].push_back(x);
    }
    for(auto &i : L) sort(i.begin(), i.end());
    for(auto &i : R) sort(i.begin(), i.end());
    int q; cin >> q;
    while(q--) {
        int x, y; cin >> x >> y;
        if(L[x].empty() || R[y].empty()) {
            cout << -1 << "\n";
            continue;
        }
        auto iter = lower_bound(L[x].begin(), L[x].end(), y);
        if(iter == L[x].end()) {
            cout << -1 << "\n";
            continue;
        }
        if(*iter == y) {
            cout << 1 << "\n";
            continue;
        }
        if(R[y][0] > x) {
            cout << -1 << "\n";
        } else cout << 2 << "\n";
    }
    return 0;
}