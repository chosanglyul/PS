#include <bits/stdc++.h>
using namespace std;

struct value {
    __int128_t p, q;
    value() { p = 0, q = 1; }
    value(__int128_t p, __int128_t q) {
        if(q < 0) p *= -1, q *= -1;
        __int128_t g = __gcd((p > 0 ? p : -p), q);
        this->p = p/g, this->q = q/g;
    }
    value operator+(const value& x) {
        return value(p*x.q+q*x.p, q*x.q);
    }
    value operator-(const value& x) {
        return value(p*x.q-q*x.p, q*x.q);
    }
    value operator*(const value& x) {
        return value(p*x.p, q*x.q);
    }
    value operator/(const value& x) {
        return value(p*x.q, q*x.p);
    }
};

istream& operator>>(istream& is, value& x) {
    int p, q;
    is >> p >> noskipws; x.p = p;
    char c; is >> c;
    if(c == '/') { is >> q; x.q = q; }
    else x.q = 1;
    is >> skipws;
    return is;
}
ostream& operator<<(ostream& os, const value& x) {
    long long p = x.p, q = x.q;
    if(x.q != 1) os << p << "/" << q;
    else os << p;
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<value>> A(n, vector<value>(m));
    for(auto &i : A) for(auto &j : i) cin >> j;
    int cnt = 0;
    int i = 0;
    while(i < m) {
        int dnt = -1;
        int j = cnt;
        while(j < n) {
            if(A[j][i].p) {
                dnt = j;
                break;
            }
            j++;
        }
        if(dnt == -1) {
            i++;
            continue;
        }
        j = 0;
        while(j < m) {
            swap(A[cnt][j], A[dnt][j]);
            j++;
        }
        value tmp = A[cnt][i];
        j = i;
        while(j < m) {
            A[cnt][j] = A[cnt][j]/tmp;
            j++;
        }
        j = 0;
        while(j < n) {
            if(j == cnt) {
                j++;
                continue;
            }
            tmp = A[j][i];
            int k = i;
            while(k < m) {
                A[j][k] = A[j][k]-(A[cnt][k]*tmp);
                k++;
            }
            j++;
        }
        cnt++;
        i++;
    }
    for(auto &i : A) {
        for(auto &j : i) cout << j << " ";
        cout << "\n";
    }
    return 0;
}