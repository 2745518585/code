#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4e5;

int n;
struct str { int id, x, y, z; } a[MAXN + 5];

struct
{
    int c[MAXN + 5];
    void clear() { for (int i = 1; i <= n; i++) c[i] = 0; }
    void update(int x, int d)
    { 
        while (x <= n) c[x] += d, x += (x & -x); 
    }
    int query(int x)
    {
        int res = 0;
        while (x) res += c[x], x -= (x & -x);
        return res;
    }
} bit;

int Ans[MAXN + 5];

void solve(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    solve(l, mid), solve(mid + 1, r);
    sort(a + l, a + r + 1, [](const str &x, const str &y) { return x.y < y.y; });
    bit.clear();
    for (int i = l; i <= r; i++)
    {
        if (a[i].x <= mid) bit.update(a[i].z, 1);
        else Ans[a[i].id] += bit.query(a[i].z);
    }
}

int main()
{
    scanf("%d", &n);
    static int x, c[MAXN + 5][4];
    for (int i = 1; i <= n; i++) a[i].id = i;
    for (int i = 1; i <= n; i++) scanf("%d", &x), a[x].x = i;
    for (int i = 1; i <= n; i++) scanf("%d", &x), a[x].y = i;
    for (int i = 1; i <= n; i++) scanf("%d", &x), a[x].z = i;

    sort(a + 1, a + n + 1, [](const str &x, const str &y) { return x.x < y.x; });
    solve(1, n);

    int Answer = 0;
    for (int i = 1; i <= n; i++) if (!Ans[i]) Answer++;
    printf("%d\n", Answer);

    return 0;
}
