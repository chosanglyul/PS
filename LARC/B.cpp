#include <bits/stdc++.h>
using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& arr) {
    out << '[';
    for (int i=0; i<arr.size(); ++i) {
        out << arr[i];
        if (i+1 < arr.size()) out << ' ';
    }
    out << ']';
    return out;
}

typedef long long ll;
typedef pair<int, int> pii;
typedef complex<double> base;

const double PI = acos(-1);
const ll M = 100;

void fft(vector<base>& a, bool inv) {
    int n = a.size();
    for (int dest=1, src=0; dest<n; ++dest) {
        int bit = n/2;
        while (src >= bit) {
            src -= bit;
            bit /= 2;
        }
        src += bit;
        if (dest < src) swap(a[dest], a[src]);
    }

    for (int len=2; len<=n; len*=2) {
        double ang = 2 * PI / len * (inv ? -1 : 1);
        base unity(cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            base w(1, 0);
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= unity;
            }
        }
    }

    if (inv) {
        for (int i=0; i<n; ++i) a[i] /= n;
    }
}

void multiply(const vector<int>& a, const vector<int>& b, vector<ll>& result) {
    int n = 2;
    while (a.size() + b.size() > n) n *= 2;

    vector<base> a1(n, 0), a2(n, 0), b1(n, 0), b2(n, 0);
    for (int i=0; i<a.size(); ++i) {
        a2[i] = a[i] % M;
        a1[i] = a[i] / M;
    }
    for (int i=0; i<b.size(); ++i) {
        b2[i] = b[i] % M;
        b1[i] = b[i] / M;
    }
    fft(a1, false);
    fft(a2, false);
    fft(b1, false);
    fft(b2, false);

    vector<base> p(n);
    result.resize(n, 0);
    for (int i=0; i<n; ++i) p[i] = a1[i] * b1[i];
    fft(p, true);
    for (int i=0; i<n; ++i) result[i] += M * M * (ll)round(p[i].real());

    for (int i=0; i<n; ++i) p[i] = a1[i] * b2[i] + a2[i] * b1[i];
    fft(p, true);
    for (int i=0; i<n; ++i) result[i] += M * (ll)round(p[i].real());

    for (int i=0; i<n; ++i) p[i] = a2[i] * b2[i];
    fft(p, true);
    for (int i=0; i<n; ++i) result[i] += (ll)round(p[i].real());
}

const int MAX_N = 1e5 + 1;
int n;
ll ans[MAX_N];

void solve(const vector<int>& fp, const vector<int>& fn, const vector<int>& cp, const vector<int>& cn) {
    vector<int> tmp, ext1, ext2;
    for (int i=0; i<min(fp.size(), cp.size()); ++i) {
        tmp.push_back(fp[fp.size()-1-i] * cp[cp.size()-1-i]);
    }
    for (int i=min(fp.size(), cp.size()); i<fp.size(); ++i) ext1.push_back(fp[fp.size()-1-i]);
    for (int i=min(fp.size(), cp.size()); i<cp.size(); ++i) ext1.push_back(cp[cp.size()-1-i]);

    for (int i=0; i<min(fn.size(), cn.size()); ++i) {
        tmp.push_back(fn[fn.size()-1-i] * cn[cn.size()-1-i]);
    }
    for (int i=min(fn.size(), cn.size()); i<fn.size(); ++i) ext2.push_back(fn[fn.size()-1-i]);
    for (int i=min(fn.size(), cn.size()); i<cn.size(); ++i) ext2.push_back(cn[cn.size()-1-i]);

    sort(tmp.begin(), tmp.end());
    for (int k=1; k<=tmp.size(); ++k) {
        ans[k] = ans[k-1] + tmp[tmp.size()-k];
    }

    if (!ext1.empty()) {
        vector<ll> result;
        reverse(ext1.begin(), ext1.end());
        reverse(ext2.begin(), ext2.end());
        multiply(ext1, ext2, result);
        // cout << ext1 << ' ' << ext2 << ' ' << result << endl;
        ans[tmp.size()+1] = ans[tmp.size()] - result[0];
        for (int k=tmp.size()+2; k<=n; ++k) {
            ans[k] = ans[k-1] - result[k-tmp.size()-1] + result[k-tmp.size()-2];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<int> fp, fn, cp, cn;
    for (int i=0; i<n; ++i) {
        int x;
        cin >> x;
        if (x >= 0) fp.push_back(x);
        else fn.push_back(abs(x));
    }
    for (int i=0; i<n; ++i) {
        int x;
        cin >> x;
        if (x >= 0) cp.push_back(x);
        else cn.push_back(abs(x));
    }
    sort(fp.begin(), fp.end());
    sort(fn.begin(), fn.end());
    sort(cp.begin(), cp.end());
    sort(cn.begin(), cn.end());

    vector<ll> ans_max(n+1);
    vector<ll> ans_min(n+1);
    solve(fp, fn, cp, cn);
    for (int i=1; i<=n; ++i) ans_max[i] = ans[i];
    solve(fn, fp, cp, cn);
    for (int i=1; i<=n; ++i) ans_min[i] = ans[i];
    for (int i=1; i<=n; ++i) {
        cout << -ans_min[i] << ' ' << ans_max[i] << '\n';
    }

    return 0;
}