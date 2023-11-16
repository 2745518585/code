#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,p=1,q,tot,t[N],b[N],c[N],rt[N];
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
    T[x].s=T[T[x].l].s+T[T[x].r].s;
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
int sum(int x,int ls,int rs,int l,int r)
{
    if(x==0) return 0;
    if(ls>=l&&rs<=r)
    {
        return T[x].s;
    }
    int z=ls+rs>>1,s=0;
    if(l<=z) s+=sum(T[x].l,ls,z,l,r);
    if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
    return s;
}
int find(int x,int ls,int rs,int k)
{
    if(ls==rs)
    {
        if(k<=T[x].s) return ls;
        return 0;
    }
    int z=ls+rs>>1;
    if(k<=T[T[x].r].s) return find(T[x].r,z+1,rs,k);
    else return find(T[x].l,ls,z,k-T[T[x].r].s);
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
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        rt[x]=merge(rt[x],rt[a[i].m],1,q);
    }
    p=find(rt[x],1,q,sum(rt[x],1,q,b[x],n)+1);
    add(rt[x],1,q,b[x],1);
    if(p>0) add(rt[x],1,q,p,-1);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        c[i]=b[i];
    }
    sort(c+1,c+n+1);
    q=unique(c+1,c+n+1)-c-1;
    for(int i=1;i<=n;++i)
    {
        b[i]=lower_bound(c+1,c+q+1,b[i])-c;
    }
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        road(x,i);
        road(i,x);
    }
    dfs(1,0);
    printf("%d",T[rt[1]].s);
    return 0;
}