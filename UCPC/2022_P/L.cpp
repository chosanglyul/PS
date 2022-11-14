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

class segtree {
    private:
    int n;
    vector<pii> seg;
    pii mer(pii a, pii b) { return {min(a.fi, b.fi), max(a.se, b.se)}; }
    void init(int i, int s, int e, vector<int>& A, vector<int>& B) {
        if(s+1 == e) seg[i] = {A[s]-B[s], A[s]+B[s]};
        else {
            init(i<<1, s, s+e>>1, A, B);
            init(i<<1|1, s+e>>1, e, A, B);
            seg[i] = mer(seg[i<<1], seg[i<<1|1]);
        }
    }
    pii query(int i, int s, int e, int l, int r) {
        if(r <= s || e <= l) return {INT_MAX, INT_MIN};
        if(l <= s && e <= r) return seg[i];
        return mer(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    public:
    segtree(vector<int>& A, vector<int>& B) {
        n = A.size();
        seg.resize(4*n);
        init(1, 0, n, A, B);
    }
    pii query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s; cin >> n >> s; --s;
    vector<int> A(n), B(n);
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;
    segtree S(A, B);
    pii ans = {A[s]-B[s], A[s]+B[s]};
    while(true) {
        int l = lower_bound(A.begin(), A.end(), ans.fi) - A.begin();
        int r = upper_bound(A.begin(), A.end(), ans.se) - A.begin();
        pii tmp = S.query(l, r);
        //cout << l << " " << r << " " << tmp << "\n";
        if(tmp == ans) break;
        else ans = tmp;
    }
    for(int i = 0; i < n; i++)
        if(ans.fi <= A[i] && A[i] <= ans.se)
            cout << i+1 << " ";
    cout << "\n";
    return 0;
}