#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,m,a[N],c[N],d[N];
bool h[N];
ll f[N],T[N];
struct str
{
    int l,r,t;
}b[N];
bool cmp(str a,str b)
{
    return a.r<b.r;
}
void add(int x,ll k)
{
    while(x<=n*2)
    {
        T[x]=(T[x]+k)%P;
        x+=(x&-x);
    }
}
ll sum(int x)
{
    ll s=0;
    while(x>=1)
    {
        s=(s+T[x])%P;
        x-=(x&-x);
    }
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&b[i].l,&b[i].r);
        b[i].t=i;
    }
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=n;++i) c[b[i].t]=i;
    int t=0;
    scanf("%d",&t);
    for(int i=1;i<=t;++i)
    {
        int x;
        scanf("%d",&x);
        x=c[x];
        h[x]=true;
    }
    int z=0;
    for(int i=n;i>=1;--i)
    {
        if(h[i]==false) continue;
        if(b[i].l<z) h[i]=false;
        else
        {
            d[i]=z;
            z=b[i].l;
        }
    }
    for(int i=1;i<=n;++i)
    {
        f[i]=((sum(n*2)-sum(b[i].l))+1)%P;
        add(b[i].l,f[i]);
    }
    for(int i=1;i<=n*2;++i) T[i]=0;
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        if(h[i]==true) s=(s+(sum(n*2)-sum(d[i]))+1)%P;
        add(b[i].l,f[i]);
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}