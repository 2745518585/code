#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MM = 2e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int N, D, a[MM];
vector<int> adj[MM];

vector<int> by_dep[MM];
int pa[MM];

unordered_set<int> vadj[MM];
int vpa[MM], vw[MM];
ll ans[MM];

struct node {
    map<int, ll> m;
    int off = 0;

    void update(int i, ll x) {
        i -= off;
        auto it = m.upper_bound(i);
        if (it == m.begin()) it = m.insert(it, { i, x });
        else {
            --it;
            if ((*it).second <= x) return;
            if ((*it).first == i) (*it).second = x;
            else it = m.insert(++it, { i, x });
        }
        auto ed = ++it;
        while (ed != m.end() && (*ed).second >= x) ++ed;
        m.erase(it, ed);
    }

    ll query(int i) {
        i -= off;
        auto it = m.upper_bound(i);
        if (it == m.begin()) return INF;
        return (*--it).second;
    }

    void merge(node& o) {
        for (auto [i, x] : o.m) {
            update(i + o.off, x);
        }
        o.m.clear();
    }
}
ns[MM];

void dfs(int u, int p, int d) {
    by_dep[d].push_back(u);
    pa[u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
    }
}

ll vdfs(int u, int d, ll x=INF) {
    if (d == 0) {
        assert(x != INF);
        x += a[u];
        ns[u].update(0, x);
        ans[u] = x;
        return x;
    }
    x = min(x, ns[u].query(D - d));
    ll up = INF;
    for (int v : vadj[u]) {
        up = min(up, vdfs(v, d - vw[v], x));
    }
    ns[u].update(d, up);
    return up;
}

void prune(int u) {
    vector<int> tmp(vadj[u].begin(), vadj[u].end());
    for (int v : tmp) prune(v);
    if (u == 1) return;
    if (adj[u].size() == 1) {
        ns[u].m.clear();
        vadj[u].clear();
        vadj[vpa[u]].erase(u);
        return;
    }
    if (vadj[u].size() == 1) {
        int v = *vadj[u].begin();
        ns[u].off += vw[v];
        if (ns[u].m.size() > ns[v].m.size()) swap(ns[u], ns[v]);
        ns[v].merge(ns[u]);
        vadj[u].clear();
        vadj[vpa[u]].erase(u);
        vadj[vpa[u]].insert(v);
        vpa[v] = vpa[u];
        vw[v] += vw[u];
    }
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> D;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1, 0);
    ns[1].m[0] = 0;
    for (int d = 1; !by_dep[d].empty(); d++) {
        for (int u : by_dep[d]) {
            vadj[pa[u]].insert(u);
            vpa[u] = pa[u];
            vw[u] = 1;
        }
        vdfs(1, d);
        prune(1);
    }
    
    for (int i = 1; i <= N; i++) {
        if (i != 1) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}