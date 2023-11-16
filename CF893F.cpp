#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,r,tot,tot2,p=1,t[N],b[N],c[N],rt[N];
struct road
{
    int m,q;
}a[N<<1];
struct tree
{
    int b,bm,d;
}T[N];
struct tree2
{
    int l,r,s;
}T2[N<<3];
bool cmp(int a,int b)
{
    return T[a].d<T[b].d;
}
void pushup(int x)
{
    T2[x].s=min(T2[T2[x].l].s,T2[T2[x].r].s);
}
void add(int &x,int ls,int rs,int q,int k)
{
    T2[++tot2]=T2[x];
    x=tot2;
    if(ls==rs)
    {
        T2[x].s=k;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T2[x].l,ls,z,q,k);
    else add(T2[x].r,z+1,rs,q,k);
    pushup(x);
}
int sum(int x,int ls,int rs,int l,int r)
{
    if(x==0) return 1e9;
    if(ls>=l&&rs<=r)
    {
        return T2[x].s;
    }
    int z=ls+rs>>1,s=1e9;
    if(l<=z) s=min(s,sum(T2[x].l,ls,z,l,r));
    if(r>z) s=min(s,sum(T2[x].r,z+1,rs,l,r));
    return s;
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x,int fa)
{
    T[x].b=++tot;
    T[x].d=T[fa].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
    }
    T[x].bm=tot;
}
int main()
{
    T2[0].s=1e9;
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    dfs(r,0);
    for(int i=1;i<=n;++i) c[i]=i;
    sort(c+1,c+n+1,cmp);
    int x=1;
    for(int i=1;i<=n;++i)
    {
        rt[i]=rt[i-1];
        while(T[c[x]].d==i)
        {
            add(rt[i],1,n,T[c[x]].b,b[c[x]]);
            ++x;
        }
    }
    scanf("%d",&m);
    int las=0;
    for(int i=1;i<=m;++i)
    {
        int x,k;
        scanf("%d%d",&x,&k);
        x=(x+las)%n+1;
        k=(k+las)%n;
        printf("%d\n",las=sum(rt[min(T[x].d+k,n)],1,n,T[x].b,T[x].bm));
    }
    return 0;
}