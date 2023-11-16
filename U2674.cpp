#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char gc(){
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf)
           + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T> inline
void read(T& x) {
    T f = 1, b = 0; char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = gc();
    } while (ch >= '0' && ch <= '9')
        b *= 10, b += ch - '0', ch = gc();
    x = f * b; return;
}
template<typename T> inline
void print(T x) {
    if (x == 0) return putchar('0'), void();
    if (x < 0) putchar('-'), x = -x;
    int st[129] = {0}, k = 0;
    while (x) st[++k] = x % 10, x /= 10;
    for (int i = k; i; i--) putchar(st[i] + '0');
}
const int N=2000001,M=6001;
int n,m,q,a2[M][M],c[N],fa[N];
ll b[N],f[N],w;
bool g[N];
bitset<M> t[M],h;
struct road
{
    int x,y;
}a[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void dfs(int x)
{
    w+=b[x];
    h[x]=0;
    for(int i=(h&t[x])._Find_first();i!=(h&t[x]).size();i=(h&t[x])._Find_next(i)) dfs(i);
}
void abc()
{
    for(int i=1;i<=m;++i)
    {
        ++a2[a[i].x][a[i].y];
        ++a2[a[i].y][a[i].x];
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(a2[i][j]!=0) t[i][j]=1;
        }
    }
    read(q);
    for(int i=1;i<=q;++i)
    {
        int k;
        read(k);
        for(int j=1;j<=k;++j)
        {
            read(c[j]);
            --a2[a[c[j]].x][a[c[j]].y];
            --a2[a[c[j]].y][a[c[j]].x];
            if(a2[a[c[j]].x][a[c[j]].y]==0) t[a[c[j]].x][a[c[j]].y]=0;
            if(a2[a[c[j]].y][a[c[j]].x]==0) t[a[c[j]].y][a[c[j]].x]=0;
        }
        ll s=1e18;
        for(int j=1;j<=n;++j) h[j]=1;
        for(int j=1;j<=n;++j)
        {
            if(h[j]==1)
            {
                w=0;
                dfs(j);
                s=min(s,w);
            }
        }
        for(int j=1;j<=k;++j)
        {
            ++a2[a[c[j]].x][a[c[j]].y];
            ++a2[a[c[j]].y][a[c[j]].x];
            if(a2[a[c[j]].x][a[c[j]].y]==1) t[a[c[j]].x][a[c[j]].y]=1;
            if(a2[a[c[j]].y][a[c[j]].x]==1) t[a[c[j]].y][a[c[j]].x]=1;
        }
        print(s);
        printf("\n");
    }
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=n;++i) read(b[i]);
    for(int i=1;i<=m;++i)
    {
        read(a[i].x),read(a[i].y);
    }
    if(n<=5000)
    {
        abc();
        return 0;
    }
    read(q);
    for(int i=1;i<=q;++i)
    {
        int k;
        read(k);
        for(int j=1;j<=k;++j)
        {
            read(c[j]);
            g[c[j]]=true;
        }
        for(int i=1;i<=n;++i) fa[i]=i;
        for(int j=1;j<=m;++j)
        {
            if(!g[j]&&find(a[j].x)!=find(a[j].y)) fa[find(a[j].x)]=find(a[j].y);
        }
        for(int j=1;j<=n;++j) f[j]=0;
        for(int j=1;j<=n;++j) f[find(j)]+=b[j];
        ll s=1e18;
        for(int j=1;j<=n;++j) if(find(j)==j) s=min(s,f[j]);
        for(int j=1;j<=k;++j) g[c[j]]=false;
        print(s);
        printf("\n");
    }
    return 0;
}