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

#define print(...) show(cout, #__VA_ARGS__, __VA_ARGS__)

template<typename H1>
std::ostream& show(std::ostream& out, const char* label, H1&& value) {
    return out << label << " = " << value << std::endl;
}

template<typename H1, typename ...T>
std::ostream& show(std::ostream& out, const char* label, H1&& value, T&&... rest) {
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
    int n, m, k; cin >> n >> m >> k;
    vector<pii> A(n);
    for(auto &i : A) cin >> i.se >> i.fi;
    sort(A.begin(), A.end());
    ll ans = 0LL;
    while(k--) {
        ans += A.back().se;
        A.pop_back();
    }
    for(auto &i : A) swap(i.fi, i.se);
    sort(A.begin(), A.end());
    while(m--) {
        ans += A.back().fi;
        A.pop_back();
    }
    cout << ans << "\n";
    return 0;
}