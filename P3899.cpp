#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=1,t[N];
ll c[N];
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
    int s,d;
}T[N];
struct str
{
    int k,t;
    str(){}
    str(int k,int t):k(k),t(t){}
};
vector<str> b[N];
int rt[N];
namespace sgt
{
    int tot;
    struct tree
    {
        int l,r;
        ll s;
    }T[N<<4];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s;
    }
    void add(int &x,int ls,int rs,int q,ll k)
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
    ll sum(int x,int ls,int rs,int l,int r)
    {
        if(x==0) return 0;
        if(ls>=l&&rs<=r)
        {
            return T[x].s;
        }
        int z=ls+rs>>1;
        ll s=0;
        if(l<=z) s+=sum(T[x].l,ls,z,l,r);
        if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
        return s;
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
}
void dfs(int x,int fa)
{
    T[x].s=1;
    T[x].d=T[fa].d+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        T[x].s+=T[a[i].m].s;
        rt[x]=sgt::merge(rt[x],rt[a[i].m],1,n);
    }
    sgt::add(rt[x],1,n,T[x].d,T[x].s-1);
    for(auto i:b[x])
    {
        c[i.t]=sgt::sum(rt[x],1,n,T[x].d+1,T[x].d+i.k)+(ll)(T[x].s-1)*min(T[x].d-1,i.k);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=m;++i)
    {
        int x,k;
        scanf("%d%d",&x,&k);
        b[x].push_back(str(k,i));
    }
    dfs(1,0);
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",c[i]);
    }
    return 0;
}