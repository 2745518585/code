#include<cstdio>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
const int N=1000001;
int n,m,a[N],b[N],S1[N],S2[N],T1,T2;
ull c[N];
struct tree
{
    int l,r,t;
    ull ms,s,s1,s2,mk,mk1,mk2,k1,k2;
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
    T[x].s1=T[x<<1].s1+T[x<<1|1].s1;
    T[x].s2=T[x<<1].s2+T[x<<1|1].s2;
    T[x].ms=T[x<<1].ms+T[x<<1|1].ms;
}
void pushnow(int x,ull mk,ull mk1,ull mk2,ull k1,ull k2,int t)
{
    T[x].ms+=t*T[x].s+mk1*T[x].s2+mk2*T[x].s1+mk*(T[x].r-T[x].l+1);
    T[x].mk+=t*T[x].k1*T[x].k2+mk1*T[x].k2+mk2*T[x].k1+mk;
    T[x].mk1+=t*T[x].k1+mk1;
    T[x].mk2+=t*T[x].k2+mk2;
    T[x].s+=k1*T[x].s2+k2*T[x].s1+k1*k2*(T[x].r-T[x].l+1);
    T[x].s1+=k1*(T[x].r-T[x].l+1);
    T[x].s2+=k2*(T[x].r-T[x].l+1);
    T[x].k1+=k1;
    T[x].k2+=k2;
    T[x].t+=t;
}
void pushdown(int x)
{
    pushnow(x<<1,T[x].mk,T[x].mk1,T[x].mk2,T[x].k1,T[x].k2,T[x].t);
    pushnow(x<<1|1,T[x].mk,T[x].mk1,T[x].mk2,T[x].k1,T[x].k2,T[x].t);
    T[x].mk=T[x].mk1=T[x].mk2=T[x].k1=T[x].k2=T[x].t=0;
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
void add1(int x,int l,int r,ull k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        pushnow(x,0,0,0,k,0,0);
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add1(x<<1,l,r,k);
    if(r>z) add1(x<<1|1,l,r,k);
    pushup(x);
}
void add2(int x,int l,int r,ull k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        pushnow(x,0,0,0,0,k,0);
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add2(x<<1,l,r,k);
    if(r>z) add2(x<<1|1,l,r,k);
    pushup(x);
}
ull sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].ms;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    ull s=0;
    if(l<=z) s+=sum(x<<1,l,r);
    if(r>z) s+=sum(x<<1|1,l,r);
    return s;
}
int main()
{
    scanf("%*d%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%llu",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%llu",&b[i]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].t=i;
    }
    sort(d+1,d+m+1,cmp);
    build(1,1,n);
    a[0]=b[0]=1e9;
    int x=1;
    for(int i=1;i<=n;++i)
    {
        add1(1,S1[T1]+1,i,a[i]);
        while(T1>=1&&a[S1[T1]]<=a[i])
        {
            add1(1,S1[T1-1]+1,S1[T1],a[i]-a[S1[T1]]);
            --T1;
        }
        S1[++T1]=i;
        add2(1,S2[T2]+1,i,b[i]);
        while(T2>=1&&b[S2[T2]]<=b[i])
        {
            add2(1,S2[T2-1]+1,S2[T2],b[i]-b[S2[T2]]);
            --T2;
        }
        S2[++T2]=i;
        pushnow(1,0,0,0,0,0,1);
        while(d[x].r==i)
        {
            c[d[x].t]=sum(1,d[x].l,d[x].r);
            ++x;
        }
    }
    for(int i=1;i<=m;++i)
    {
        printf("%llu\n",c[i]);
    }
    return 0;
}