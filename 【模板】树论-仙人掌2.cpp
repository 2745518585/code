#include<bits/stdc++.h>
using namespace std;
const int N=2000001;
int n,m,s,p=1,t[N],f[N],fa[N],ga[N],b[N],Q[N];
bool g[N],h[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void check(int x,int y)
{
    while(y!=x)
    {
        g[ga[y]]=g[ga[y]^1]=true;
        y=fa[y];
    }
}
void solve(int x,int y)
{
    int n=0;
    b[++n]=x;
    while(y!=x)
    {
        b[++n]=y;
        y=fa[y];
    }
    for(int i=1;i<=n;++i) b[n+i]=b[i];
    int T=1,R=0;
    for(int i=1;i<=n*2;++i)
    {
        while(T<=R&&i-Q[T]>n/2) ++T;
        if(T<=R) s=max(s,f[b[Q[T]]]+f[b[i]]+(i-Q[T]));
        while(T<=R&&f[b[Q[R]]]-Q[R]<=f[b[i]]-i) --R;
        Q[++R]=i;
    }
    for(int i=2;i<=n;++i)
    {
        f[x]=max(f[x],f[b[i]]+min(i-1,n-i+1));
    }
}
void dfs(int x)
{
    h[x]=true;
    int u=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa[x]) continue;
        if(h[a[i].m])
        {
            if(g[i]==false)
            {
                g[i]=g[i^1]=true;
                check(a[i].m,x);
            }
            else solve(x,a[i].m);
            continue;
        }
        fa[a[i].m]=x;
        ga[a[i].m]=i;
        dfs(a[i].m);
        if(g[i]==false)
        {
            s=max(s,f[x]+f[a[i].m]+1);
            f[x]=max(f[x],f[a[i].m]+1);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int k;
        scanf("%d",&k);
        int x,y;
        scanf("%d",&x);
        for(int j=2;j<=k;++j)
        {
            scanf("%d",&y);
            if(x!=0)
            {
                road(x,y);
                road(y,x);
            }
            x=y;
        }
    }
    dfs(1);
    printf("%d",s);
    return 0;
}