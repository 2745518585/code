#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 2e5 + 10;
ll n, m;
ll sum[N];
ll l[N], r[N], c[N], t[N];
vector<ll> jl[N], jr[N];
ll u[N], v[N];
struct s1
{
    ll val[N << 2], tag[N << 2];
    inline void clear()
    {
        memset(val, 0, sizeof(val));
        memset(tag, 0, sizeof(tag));
        return;
    }
    inline void push(ll o, ll x)
    {
        val[o] += x;
        tag[o] += x;
        return;
    }
    inline void pushup(ll o)
    {
        val[o] = min(val[o << 1], val[o << 1 | 1]);
        return;
    }
    inline void pushdown(ll o)
    {
        if (tag[o])
        {
            push(o << 1, tag[o]);
            push(o << 1 | 1, tag[o]);
            tag[o] = 0;
        }
        return;
    }
    inline void update(ll o, ll l, ll r, ll x, ll y, ll z)
    {
        if (x <= l && r <= y)
        {
            push(o, z);
            return;
        }
        ll mid = (l + r) >> 1;
        pushdown(o);
        if (mid >= x) update(o << 1, l, mid, x, y, z);
        if (mid < y) update(o << 1 | 1, mid + 1, r, x, y, z);
        pushup(o);
        return;
    }
    inline ll ask(ll o, ll l, ll r, ll x, ll y)
    {
        if (x <= l && r <= y) return val[o];
        ll mid = (l + r) >> 1;
        pushdown(o);
        if (mid < x) return ask(o << 1 | 1, mid + 1, r, x, y);
        if (mid >= y) return ask(o << 1, l, mid, x, y);
        return min(ask(o << 1, l, mid, x, y), ask(o << 1 | 1, mid + 1, r, x, y));
    }
} o;
struct s2
{
    ll val[N << 2], ans[N << 2], tag[N << 2], tg[N << 2];
    inline void pushup(ll o)
    {
        val[o] = min(val[o << 1], val[o << 1 | 1]);
        ans[o] = min(ans[o << 1], ans[o << 1 | 1]);
        return;
    }
    inline void push(ll o, ll x, ll y)
    {
        ans[o] = min(ans[o], val[o] + y);
        tg[o] = min(tg[o], tag[o] + y);
        val[o] += x;
        tag[o] += x;
        return;
    }
    inline void pushdown(ll o)
    {
        if (tag[o] || tg[o]) push(o << 1, tag[o], tg[o]), push(o << 1 | 1, tag[o], tg[o]), tag[o] = tg[o] = 0;
        return;
    }
    inline void update(ll o, ll l, ll r, ll x, ll y, ll z)
    {
        if (x <= l && r <= y)
        {
            push(o, z, z);
            return;
        }
        ll mid = (l + r) >> 1;
        pushdown(o);
        if (mid >= x) update(o << 1, l, mid, x, y, z);
        if (mid < y) update(o << 1 | 1, mid + 1, r, x, y, z);
        pushup(o);
        return;
    }
    inline ll ask(ll o, ll l, ll r, ll x, ll y)
    {
        if (x <= l && r <= y) return ans[o];
        ll mid = (l + r) >> 1;
        pushdown(o);
        if (mid < x) return ask(o << 1 | 1, mid + 1, r, x, y);
        if (mid >= y) return ask(o << 1, l, mid, x, y);
        return min(ask(o << 1, l, mid, x, y), ask(o << 1 | 1, mid + 1, r, x, y));
    }
} p;
vector<ll> rc[N];
int main()
{
    // freopen("test1.in","r",stdin);freopen("test1.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    ll an = 0;
    for (int i = 1; i <= n; i++) cin >> sum[i], sum[i] += sum[i - 1];
    for (int i = 1; i <= m; i++)
    {
        cin >> l[i] >> r[i] >> c[i] >> t[i];
        an += c[i];
        if (!t[i]) jl[l[i]].emplace_back(i), jr[r[i]].emplace_back(i);
        rc[l[i] + 1].emplace_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        for (auto t : jr[i]) o.update(1, 1, n, 1, l[t], -c[t]);
        o.update(1, 1, n, i, i, u[i - 1] - sum[i - 1]);
        u[i] = min(u[i - 1], sum[i] + o.ask(1, 1, n, 1, i));
    }
    o.clear();
    for (int i = n; i >= 1; i--)
    {
        for (auto t : jl[i]) o.update(1, 1, n, r[t], n, -c[t]);
        o.update(1, 1, n, i, i, v[i + 1] + sum[i]);
        v[i] = min(v[i + 1], o.ask(1, 1, n, i, n) - sum[i - 1]);
    }
    for (int i = 1; i <= n; i++) p.update(1, 1, n, i, i, v[i + 1] + sum[i]);
    for (int i = 1; i <= m; i++) p.update(1, 1, n, r[i], n, -c[i]);
    for (int i = 1; i <= n; i++)
    {
        for (auto o : rc[i]) p.update(1, 1, n, r[o], n, c[o]);
        p.update(1, 1, n, 1, n, u[i - 1] - sum[i - 1]);
        p.update(1, 1, n, 1, n, sum[i - 1] - u[i - 1]);
        cout << an + min(u[n], p.ask(1, 1, n, i, n)) << ' ';
    }
    return 0;
}