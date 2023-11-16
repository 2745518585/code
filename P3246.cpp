#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],S[N],T1;
ll c[N];
struct tree
{
    int l,r,t;
    ll s,ms,k,mk;
}T[N<<2];
struct str
{
    int l,r,t;
}d[N];
bool cmp(str a,str b)
{
    return a.r<b.r;
}
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
    T[x].ms=T[x<<1].ms+T[x<<1|1].ms;
}
void pushnow(int x,ll k,ll mk,int t)
{
    T[x].ms+=t*T[x].s+mk*(T[x].r-T[x].l+1);
    T[x].mk+=t*T[x].k+mk;
    T[x].s+=k*(T[x].r-T[x].l+1);
    T[x].k+=k;
    T[x].t+=t;
}
void pushdown(int x)
{
    pushnow(x<<1,T[x].k,T[x].mk,T[x].t);
    pushnow(x<<1|1,T[x].k,T[x].mk,T[x].t);
    T[x].k=T[x].mk=T[x].t=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,ll k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s+=k*(T[x].r-T[x].l+1);
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
ll sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].ms;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ll s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].t=i;
    }
    sort(d+1,d+m+1,cmp);
    build(1,1,n);
    a[0]=1e9;
    int x=1;
    for(int i=1;i<=n;++i)
    {
        add(1,S[T1]+1,i,a[i]);
        while(T1>=1&&a[S[T1]]>=a[i])
        {
            add(1,S[T1-1]+1,S[T1],a[i]-a[S[T1]]);
            --T1;
        }
        S[++T1]=i;
        pushnow(1,0,0,1);
        while(d[x].r==i)
        {
            c[d[x].t]=sum(1,d[x].l,d[x].r);
            ++x;
        }
    }
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",c[i]);
    }
    return 0;
}