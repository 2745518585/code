#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=2000001;
int n,m,tot,a[N],b[N],fa[N],r[N],f[N],g[N];
vector<int> c[N];
struct tree
{
    int d,b,bm;
}T[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void dfs(int x,int rt)
{
    r[x]=rt;
    T[x].b=++tot;
    for(auto i:c[x])
    {
        if(g[i]) continue;
        T[i].d=T[x].d+1;
        dfs(i,rt);
    }
    T[x].bm=tot;
}
int dis(int x,int y)
{
    if(find(x)!=find(y)) return 1e9;
    int p=find(x);
    if(g[y]) return (g[y]-g[r[x]]+f[p])%f[p]+T[x].d;
    if(T[x].b>=T[y].b&&T[x].b<=T[y].bm) return T[x].d-T[y].d;
    else return 1e9;
}
bool check(int k)
{
    int x=1;
    for(int i=1;i<=m;++i)
    {
        while(x<=n&&dis(a[i],x)>k) ++x;
    }
    return x<=n;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&m,&n);
        for(int i=1;i<=n;++i) fa[i]=i,c[i].clear(),g[i]=0;
        tot=0;
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
            c[b[i]].push_back(i);
            fa[find(i)]=find(b[i]);
        }
        for(int i=1;i<=n;++i)
        {
            if(i!=find(i)) continue;
            int x=b[i],p=0;
            g[i]=++p;
            while(x!=i) g[x]=++p,x=b[x];
            f[i]=p;
        }
        for(int i=1;i<=n;++i)
        {
            if(g[i])
            {
                T[i].d=0;
                dfs(i,i);
            }
        }
        int l=0,r=n+1;
        while(l<r)
        {
            int z=l+r>>1;
            if(check(z)) r=z;
            else l=z+1;
        }
        if(l==n+1) printf("-1\n");
        else printf("%d\n",l);
    }
    return 0;
}