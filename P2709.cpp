#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,k,q,a[N],b[N];
ll s,c[N];
struct str
{
    int l,r,t;
}d[N];
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
    scanf("%d%d%d",&n,&m,&k);
    q=sqrt(n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].t=i;
    }
    sort(d+1,d+m+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;++i)
    {
        while(l>d[i].l) add(a[--l]);
        while(r<d[i].r) add(a[++r]);
        while(l<d[i].l) del(a[l++]);
        while(r>d[i].r) del(a[r--]);
        c[d[i].t]=s;
    }
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",c[i]);
    }
    return 0;
}