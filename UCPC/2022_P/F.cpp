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

const int INF = 1e9;

struct SegmentTree {
    int size;
    vector<int> tree;
    vector<int> lazy;
    SegmentTree(int size) : size(size) {
        tree.resize(4*size, 0);
        lazy.resize(4*size, 0);
    }

    void update_lazy(int n, int nl, int nr) {
        if (lazy[n] != 0) {
            tree[n] += lazy[n];
            if (nl != nr) {
                lazy[2*n] += lazy[n];
                lazy[2*n+1] += lazy[n];
            }
            lazy[n] = 0;
        }
    }

    int query(int l, int r, int n, int nl, int nr) {
        update_lazy(n, nl, nr);
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return tree[n];
        int mid = (nl + nr) / 2;
        return max(query(l, r, 2*n, nl, mid), query(l, r, 2*n+1, mid+1, nr));
    }

    int query(int l, int r) {
        return query(l, r, 1, 0, size-1);
    }

    void add(int l, int r, int val, int n, int nl, int nr) {
        update_lazy(n, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] += val;
            update_lazy(n, nl, nr);
            return;
        }
        int mid = (nl + nr) / 2;
        add(l, r, val, 2*n, nl, mid);
        add(l, r, val, 2*n+1, mid+1, nr);
        tree[n] = max(tree[2*n], tree[2*n+1]);
    }

    void add(int l, int r, int val) {
        add(l, r, val, 1, 0, size-1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> mon(n+1, 0);
    for (int i=1; i<=n; ++i) {
        cin >> mon[i];
    }

    SegmentTree seg(n+1);
    vector<int> last_freq(k+1, -1);
    vector<int> dp(n+1, 0);
    for (int i=1; i<=n; ++i) {
        // add i'th num
        if (mon[i] != 0) {
            seg.add(last_freq[mon[i]], i-1, 1);
            last_freq[mon[i]] = i;
        }
        // for (int j=0; j<=i; ++j) print(j, seg.query(j, j));
        dp[i] = seg.query(0, i - ((k+1)/2));
        seg.add(i, i, dp[i]);
        // print(i, dp[i], last_freq);
    }
    // print(dp);

    int accum = 0;
    int ans = dp[n];
    fill(last_freq.begin(), last_freq.end(), -1);
    for (int i=n-1; i>=0; --i) {
        // print(i, ans, accum);
        // (i+1)'th num
        if (mon[i+1] != 0 && last_freq[mon[i+1]] == -1) {
            accum++;
            last_freq[mon[i+1]] = i+1;
        }
        ans = max(ans, dp[i] + accum);
    }
    cout << ans;
    return 0;
}