#include<cstdio>
#include<algorithm>
using namespace std;
const int N=500001,M=21;
int n,m,q,k,p=1,t[N],b[N],b2[N],c[N],d[N],fat[N][M],fa[N][M],ga[N][M];
struct road
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
int tot,rt[N];
struct tree
{
    int l,r,s;
}T[N<<4];
void add(int &x,int ls,int rs,int q,int k)
{
    T[++tot]=T[x];
    x=tot;
    if(ls==rs)
    {
        T[x].s=k;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
}
int sum(int x,int ls,int rs,int q)
{
    if(x==0) return 0;
    if(ls==rs)
    {
        return T[x].s;
    }
    int z=ls+rs>>1;
    if(q<=z) return sum(T[x].l,ls,z,q);
    else return sum(T[x].r,z+1,rs,q);
}
void dfs(int x,int fa)
{
    d[x]=d[fa]+1;
    fat[x][0]=fa;
    rt[x]=rt[fa];
    if(b2[c[x]]!=0) add(rt[x],1,k,b2[c[x]],x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
    }
}
int LCA(int x,int y)
{
    if(d[x]<d[y]) swap(x,y);
    int t=0;
    while(t>=0)
    {
        if(d[fat[x][t]]>=d[y]) x=fat[x][t],++t;
        else --t;
    }
    if(x==y) return x;
    t=0;
    while(t>=0)
    {
        if(fat[x][t]!=fat[y][t]) x=fat[x][t],y=fat[y][t],++t;
        else --t;
    }
    return fat[x][0];
}
int check1(int x,int y)
{
    x=sum(rt[x],1,k,1);
    if(d[x]<d[y]+1) return 0;
    int t=0,w=1;
    while(t>=0)
    {
        if(d[fa[x][t]]>=d[y]+1) x=fa[x][t],w+=(1<<t),++t;
        else --t;
    }
    return w;
}
int check2(int x,int y,int z)
{
    x=sum(rt[x],1,k,z);
    if(d[x]<d[y]) return k+1;
    int t=0,w=z;
    while(t>=0)
    {
        if(d[ga[x][t]]>=d[y]) x=ga[x][t],w-=(1<<t),++t;
        else --t;
    }
    return w;
}
int main()
{
    scanf("%d%*d%d",&n,&k);
    for(int i=1;i<=k;++i)
    {
        scanf("%d",&b[i]);
        b2[b[i]]=i;
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&c[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs(1,0);
    for(int i=1;i<=n;++i)
    {
        if(b2[c[i]]!=0&&b2[c[i]]+1<=k) fa[i][0]=sum(rt[i],1,k,b2[c[i]]+1);
        else fa[i][0]=0;
        if(b2[c[i]]!=0&&b2[c[i]]-1>=1) ga[i][0]=sum(rt[i],1,k,b2[c[i]]-1);
        else ga[i][0]=0;
    }
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=n;++j)
        {
            fa[j][i]=fa[fa[j][i-1]][i-1];
            ga[j][i]=ga[ga[j][i-1]][i-1];
            fat[j][i]=fat[fat[j][i-1]][i-1];
        }
    }
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int lca=LCA(x,y);
        int p=check1(x,lca);
        int l=p,r=k;
        while(l<r)
        {
            int z=l+r+1>>1;
            if(check2(y,lca,z)<=p+1) l=z;
            else r=z-1;
        }
        printf("%d\n",l);
    }
    return 0;
}