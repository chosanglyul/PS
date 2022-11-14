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

struct Vertex {
    int l, r, val;
};

const int MAX_N = 5e5 + 1;
int n;
vector<int> arr;

Vertex vs[4*MAX_N];
vector<int> adj[4*MAX_N];
vector<int> radj[4*MAX_N];
int node_num[MAX_N];

void init(int n, int nl, int nr) {
    if (nl == nr) {
        vs[n] = {nl,nr,arr[nl]};
        node_num[nl] = n;
        return;
    }

    int mid = (nl + nr) / 2;
    init(2*n, nl, mid);
    init(2*n+1, mid+1, nr);
    vs[n] = {nl,nr,max(vs[2*n].val, vs[2*n+1].val)};

    adj[2*n].push_back(n);
    adj[2*n+1].push_back(n);
    radj[n].push_back(2*n);
    radj[n].push_back(2*n+1);
}

void add_edge(int orig_from, int l, int r, int n, int nl, int nr) {
    if (r < nl || nr < l) return;
    if (l <= nl && nr <= r) {
        adj[n].push_back(node_num[orig_from]);
        radj[node_num[orig_from]].push_back(n);
        return;
    }
    int mid = (nl + nr) / 2;
    add_edge(orig_from, l, r, 2*n, nl, mid);
    add_edge(orig_from, l, r, 2*n+1, mid+1, nr);
}

int scc[4*MAX_N];
int scc_counter = 0;
vector<vector<int>> sadj;
vector<int> smax, indeg;
stack<int> st;
bool visited[4*MAX_N];

void dfs(int here) {
    visited[here] = true;
    for (int there: adj[here]) {
        if (!visited[there]) {
            dfs(there);
        }
    }
    st.push(here);
}

void back_dfs(int here) {
    visited[here] = true;
    scc[here] = scc_counter;
    smax[scc[here]] = max(smax[scc[here]], vs[here].val);
    for (int there: radj[here]) {
        if (!visited[there]) {
            back_dfs(there);
        } else if (scc[there] != scc[here]) {
            sadj[scc[there]].push_back(scc[here]);
            indeg[scc[here]]++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    arr.resize(n);
    for (int& x: arr) cin >> x;

    init(1, 0, n-1);
    for (int i=0; i<n; ++i) {
        int l, r;
        cin >> l >> r;
        add_edge(i, l-1, r-1, 1, 0, n-1);
    }

    // scc
    memset(visited, false, sizeof visited);
    for (int i=0; i<n; ++i) {
        int here = node_num[i];
        if (!visited[here]) dfs(here);
    }

    memset(visited, false, sizeof visited);
    while (!st.empty()) {
        int here = st.top();
        st.pop();
        if (!visited[here]) {
            sadj.push_back(vector<int>());
            smax.push_back(0);
            indeg.push_back(0);
            back_dfs(here);
            scc_counter++;
        }
    }

    // topo sort
    queue<int> q;
    for (int i=0; i<scc_counter; ++i) {
        if (indeg[i] == 0) {
            q.push(i);  
        }
    }

    while (!q.empty()) {
        int here = q.front();
        q.pop();
        for (int there: sadj[here]) {
            smax[there] = max(smax[there], smax[here]);
            if (--indeg[there] == 0) q.push(there);
        }
    }
    for (int i=0; i<n; ++i) {
        cout << smax[scc[node_num[i]]] << ' ';
    }
    return 0;
}