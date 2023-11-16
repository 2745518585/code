#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001;
int n,p=1,q,tot,t[N],c[N],d[N],rt[N];
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
struct tree
{
    int l,r,s;
}T[N<<4];
void pushup(int x)
{
    T[x].s=max(T[T[x].l].s,T[T[x].r].s);
}
void add(int &x,int ls,int rs,int q,int k)
{
    if(x==0) x=++tot;
    if(ls==rs)
    {
        T[x].s+=k;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q,k);
    else add(T[x].r,z+1,rs,q,k);
    pushup(x);
}
int sum(int x,int ls,int rs)
{
    if(ls==rs) return ls;
    int z=ls+rs>>1;
    if(T[T[x].l].s>=T[T[x].r].s) return sum(T[x].l,ls,z);
    else return sum(T[x].r,z+1,rs);
}
int merge(int x1,int x2,int ls,int rs)
{
    if(x1==0||x2==0) return x1+x2;
    if(ls==rs)
    {
        T[x1].s=T[x1].s+T[x2].s;
        return x1;
    }
    int z=ls+rs>>1;
    T[x1].l=merge(T[x1].l,T[x2].l,ls,z);
    T[x1].r=merge(T[x1].r,T[x2].r,z+1,rs);
    pushup(x1);
    return x1;
}
void dfs(int x,int fa)
{
    d[x]=d[fa]+1;
    add(rt[x],1,n,d[x],1);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        rt[x]=merge(rt[x],rt[a[i].m],1,n);
    }
    c[x]=sum(rt[x],1,n);
}
int main()
{
    scanf("%d",&n);
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
        printf("%d\n",c[i]-d[i]);
    }
    return 0;
}