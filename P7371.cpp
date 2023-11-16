#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1200001;
int n,m;
struct str
{
    int w,h;
}a[N];
struct tree
{
    int l,r,s2;
    ll s;
}T[N<<2];
bool cmp(str a,str b)
{
    return a.h<b.h;
}
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
    T[x].s2=T[x<<1].s2+T[x<<1|1].s2;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=T[x].s2=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,int q,ll k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s+=k;
        ++T[x].s2;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
ll sum(int x,ll k)
{
    if(T[x].l==T[x].r) return k*T[x].l;
    if(k<=T[x<<1].s2) return sum(x<<1,k);
    else return T[x<<1].s+sum(x<<1|1,k-T[x<<1].s2);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].w,&a[i].h);
    }
    sort(a+1,a+n+1,cmp);
    build(1,1,1e6);
    ll s=1e18;
    for(int i=1;i<=m-1;++i) add(1,a[i].w,a[i].w);
    for(int i=m;i<=n;++i)
    {
        add(1,a[i].w,a[i].w);
        s=min(s,a[i].h*sum(1,m));
    }
    printf("%lld",s);
    return 0;
}