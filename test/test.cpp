#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define Rep(i,l,r) for (int i = (l); i <= (r); ++ i)
#define RepD(i,r,l) for (int i = (r); i >= (l); -- i)
#define RepG(i,x) for (int i = hd[x]; i; i = e[i].nxt)
#define mkp make_pair
#define uu first
#define vv second
#define ls (o<<1)
#define rs (o<<1|1)

typedef long long ll;
typedef pair <int, int> pii;

const int N = 2e5+5;

int n, q, a[N];
struct node {
    vector <pii> pr, su; ll s;
    node () {pr.clear(), su.clear(), s = 0;}
} tr[N<<2];

int gcd (int x, int y) {return y? gcd (y, x%y): x;}

inline vector <pii> hb (vector <pii> x, vector <pii> y, int ty) {
    if (x.empty()) return y; if (y.empty()) return x;
    if (ty) reverse (x.begin(), x.end()), reverse (y.begin(), y.end());
    vector <pii> res; res.clear(); int szx = x.size()-1, szy = y.size()-1; pii t;
    Rep(i,0,szx) t = x[i], res.push_back(t);
    Rep(i,0,szy) {
        int gc = gcd (x[szx].uu, y[i].uu);
        if (gc==t.uu) t.vv = y[i].vv, res[res.size()-1].vv = t.vv+x[szx].vv;
        else t.uu = gc, t.vv = y[i].vv, res.push_back(mkp(t.uu,t.vv+x[szx].vv));
    }
    if (ty) reverse (res.begin(), res.end());
    return res;
}

inline node mg (node x, node y) {
    node res; res.s = x.s+y.s;
    res.pr = hb (x.pr, y.pr, 0), res.su = hb (y.su, x.su, 1);
    int szx = x.su.size()-1, szy = y.pr.size()-1;
    if (szx<0 || szy<0) return res;
    int j = 0;
    Rep(i,0,szx) {
        while (j<=szy && gcd (x.su[i].uu, y.pr[j].uu)>1) ++ j;
        ll t = x.su[i].vv; if (i<szx) t -= x.su[i+1].vv;
        if (j) res.s += t*y.pr[j-1].vv;
    }
    return res;
}

inline void fz (node &x, int v) {
    x.pr.clear (), x.su.clear ();
    x.pr.push_back(mkp(v,1)), x.su.push_back(mkp(v,1));
    x.s = (v>1);
}

inline void pushup (int o) {tr[o] = mg (tr[ls], tr[rs]);}

void build (int o, int l, int r) {
    if (l==r) {fz (tr[o], a[l]); return;}
    int mid = (l+r)>>1;
    build (ls, l, mid), build (rs, mid+1, r);
    pushup (o);
}

void modi (int o, int l, int r, int q, int v) {
    if (l==r) {fz (tr[o], v); return;}
    int mid = (l+r)>>1;
    if (q<=mid) modi (ls, l, mid, q, v);
    else modi (rs, mid+1, r, q, v);
    pushup (o);
}

node qans (int o, int l, int r, int ql, int qr) {
    if (ql<=l && qr>=r) return tr[o];
    int mid = (l+r)>>1; node res;
    if (ql<=mid && qr>mid) {
        res = mg (qans (ls, l, mid, ql, qr), qans (rs, mid+1, r, ql, qr));
        return res;
    }
    else if (ql<=mid) res = qans (ls, l, mid, ql, qr);
    else if (qr>mid) res = qans (rs, mid+1, r, ql, qr);
    return res;
}

inline int read () {
    int z = 0, f = 1; char c = getchar ();
    while (c<'0' || c>'9') {if (c=='-') f = -1; c = getchar ();}
    while (c>='0' && c<='9') z = z*10+c-'0', c = getchar ();
    return z*f;
}

int main () {
    int ty, l, r, x, v;
    n = read (), q = read ();
    Rep(i,1,n) a[i] = read ();
    build (1, 1, n);
    while (q --) {
        ty = read ();
        if (ty==1) x = read (), v = read (), modi (1, 1, n, x, v);
        else l = read (), r = read (), printf ("%lld\n", qans (1, 1, n, l, r).s);
    }
    return 0;
}
