#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
const int N=1000001;
int n,k,m,q,b[N],e[N];
set<int> Set[N];
struct str
{
    int x,k,t,u;
    str() {}
    str(int x,int k,int t,int u):x(x),k(k),t(t),u(u) {}
}c[N];
struct str2
{
    int x,k,t1,t2;
}c2[N];
bool cmp(str a,str b)
{
    if(a.t!=b.t) return a.t<b.t;
    return a.u<b.u;
}
bool cmp2(str2 a,str2 b)
{
    return a.x<b.x;
}
struct tree
{
    int l,r,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=min(T[x<<1].s,T[x<<1|1].s);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=n+1;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=k;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(r<T[x].l||l>T[x].r||l>r) return n+1;
    if(T[x].l>=l&&T[x].r<=r) return T[x].s;
    int z=T[x].l+T[x].r>>1,s=n+1;
    if(l<=z) s=min(s,sum(x<<1,l,r));
    if(r>z) s=min(s,sum(x<<1|1,l,r));
    return s;
}
bool check(int x,int t)
{
    int p=sum(1,t+1,n+k);
    if(p==0||(b[t+1]-1)-x<x-b[p]) return false;
    return true;
}
void solve(str x)
{
    if(x.u==1)
    {
        int z1=*prev(Set[x.k].upper_bound(x.x)),z2=*Set[x.k].upper_bound(x.x);
        Set[x.k].insert(x.x);
        add(1,x.x,z1);
        add(1,z2,x.x);
    }
    else if(x.u==2)
    {
        Set[x.k].erase(x.x);
        int z1=*prev(Set[x.k].upper_bound(x.x)),z2=*Set[x.k].upper_bound(x.x);
        add(1,x.x,n+1);
        add(1,z2,z1);
    }
    else if(x.u==3)
    {
        int l=min((int)(lower_bound(b+1,b+n+1,x.x)-b),n),r=n+1;
        while(l<r)
        {
            int z=l+r>>1;
            if(check(x.x,z)) r=z;
            else l=z+1;
        }
        if(l==n+1) e[x.k]=-1;
        else
        {
            int p=sum(1,l+1,n+k);
            e[x.k]=max(b[l]-x.x,x.x-b[p]);
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&k,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d%d",&c2[i].x,&c2[i].k,&c2[i].t1,&c2[i].t2);
    }
    sort(c2+1,c2+n+1,cmp2);
    for(int i=1;i<=n;++i) b[i]=c2[i].x;
    b[n+1]=1e9;
    for(int i=1;i<=n;++i)
    {
        c[++q]=str(i,c2[i].k,c2[i].t1,1);
        c[++q]=str(i,c2[i].k,c2[i].t2+1,2);
    }
    for(int i=1;i<=m;++i)
    {
        int x,t;
        scanf("%d%d",&x,&t);
        c[++q]=str(x,i,t,3);
    }
    sort(c+1,c+q+1,cmp);
    build(1,1,n+k);
    for(int i=1;i<=k;++i)
    {
        Set[i].insert(0);
        Set[i].insert(n+i);
        add(1,n+i,0);
    }
    int x=0;
    while(x<q)
    {
        solve(c[++x]);
        while(c[x+1].t==c[x].t) solve(c[++x]);
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",e[i]);
    }
    return 0;
}