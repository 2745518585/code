#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,tot,b[N],rt1[N],rt[N];
ll s;
vector<int> c[N];
vector<pair<int,int>> a[N];
struct str
{
    int k,t;
    ll s;
    str():k(0),t(0),s(0) {}
};
str check(str a,str b,int n)
{
    int m=(n+1)/2;
    str c;
    if(a.k==0)
    {
        c.s=(a.s+b.s+(ll)(m-a.t)*b.t+(ll)a.t*((n-m)-b.t))%P;
        c.t=a.t+b.t;
        c.k=a.k^b.k;
    }
    else
    {
        c.s=(a.s+b.s+(ll)(m-a.t)*((n-m)-b.t)+(ll)a.t*b.t)%P;
        c.t=a.t+((n-m)-b.t);
        c.k=a.k^b.k;
    }
    return c;
}
struct tree
{
    int l,r;
    str s;
}T[N<<4];
void pushup(int x,int n)
{
    T[x].s=check(T[T[x].l].s,T[T[x].r].s,n);
}
void add(int &x,int ls,int rs,int q)
{
    if(q<ls||q>rs) return;
    if(x==0) x=++tot;
    if(ls==rs)
    {
        T[x].s.k^=1;
        T[x].s.t^=1;
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T[x].l,ls,z,q);
    else add(T[x].r,z+1,rs,q);
    pushup(x,rs-ls+1);
}
int merge(int x1,int x2,int ls,int rs)
{
    if(x1==0||x2==0) return x1+x2;
    if(ls==rs)
    {
        T[x1].s.k^=T[x2].s.k;
        T[x1].s.t^=T[x2].s.t;
        return x1;
    }
    int z=ls+rs>>1;
    T[x1].l=merge(T[x1].l,T[x2].l,ls,z);
    T[x1].r=merge(T[x1].r,T[x2].r,z+1,rs);
    pushup(x1,rs-ls+1);
    return x1;
}
void dfs(int x,int fa,int k)
{
    for(auto i:a[x])
    {
        if(i.first==fa) continue;
        dfs(i.first,x,i.second);
        rt1[x]=merge(rt1[x],rt1[i.first],0,(m-1)/2);
        rt[x]=merge(rt[x],rt[i.first],0,m/2);
    }
    for(auto i:c[x])
    {
        if(i/2<=(m-1)/2) add(rt1[x],0,(m-1)/2,i/2);
        if((i+1)/2<=m/2) add(rt[x],0,m/2,(i+1)/2);
    }
    s=(s+(T[rt1[x]].s.s+T[rt[x]].s.s)*k)%P;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&b[i]);
        c[b[i]].push_back(i);
    }
    dfs(1,0,0);
    printf("%lld",s);
    return 0;
}