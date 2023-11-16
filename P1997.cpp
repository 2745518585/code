#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=500001;
int n,m,q,k;
ll a[N],b[N],c[N],e[N],s;
struct str
{
    int l,r,k;
}d[N];
bool cmp(str a,str b)
{
    if((a.l-1)/q!=(b.l-1)/q) return a.l<b.l;
    return a.r<b.r;
}
void add(int x)
{
    ++b[x];
    s=max(s,b[x]);
}
void del(int x)
{
    --b[x];
}
int main()
{
    scanf("%d%d",&n,&m);
    q=sqrt(n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        e[i]=a[i];
    }
    sort(e+1,e+n+1);
    k=unique(e,e+n+1)-e-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(e+1,e+k+1,a[i])-e;
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].k=i;
    }
    sort(d+1,d+m+1,cmp);
    d[0].l=-1e9;
    int l=1,r=0;
    ll s0=-1e18;
    for(int i=1;i<=m;++i)
    {
        if((d[i].l-1)/q!=(d[i-1].l-1)/q)
        {
            while(r>l-1) del(a[r--]);
            l=(d[i].l-1)/q*q+q,r=l-1;
            s0=-1e18;
        }
        if((d[i].l-1)/q==(d[i].r-1)/q)
        {
            s=-1e18;
            for(int j=d[i].l;j<=d[i].r;++j) add(a[j]);
            for(int j=d[i].l;j<=d[i].r;++j) del(a[j]);
            c[d[i].k]=s;
            continue;
        }
        while(l<(d[i].l-1)/q*q+q) del(a[l++]);
        s=s0;
        while(d[i].r>r) add(a[++r]);
        s0=s;
        while(d[i].l<l) add(a[--l]);
        c[d[i].k]=s;
    }
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",c[i]);
    }
    return 0;
}