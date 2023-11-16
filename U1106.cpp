#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100001;
int n,m,q,a[N],b[N],e[N];
ll c[N],s;
struct str
{
    int l,r,k;
}d[N];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
bool cmp(str a,str b)
{
    if((a.l-1)/q!=(b.l-1)/q) return a.l<b.l;
    return a.r<b.r;
}
void add(int x)
{
    s+=b[x]*2+1;
    ++b[x];
}
void del(int x)
{
    s-=b[x]*2-1;
    --b[x];
}
int main()
{
    scanf("%d%d",&n,&m);
    q=sqrt(n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].k=i;
        e[i]=(d[i].r-d[i].l+1);
    }
    sort(d+1,d+m+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;++i)
    {
        while(d[i].l<l) add(a[--l]);
        while(d[i].r>r) add(a[++r]);
        while(d[i].l>l) del(a[l++]);
        while(d[i].r<r) del(a[r--]);
        c[d[i].k]=s;
    }
    for(int i=1;i<=m;++i)
    {
        ll x=c[i]-e[i],y=(ll)e[i]*(e[i]-1);
        ll z=gcd(x,y);
        printf("%lld/%lld\n",x/z,y/z);
    }
    return 0;
}