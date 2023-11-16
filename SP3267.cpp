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
    int l,r,k;
}d[N];
bool cmp(str a,str b)
{
    if((a.l-1)/q!=(b.l-1)/q) return a.l<b.l;
    return a.r<b.r;
}
void add(int x)
{
    if(b[x]==0) ++s;
    ++b[x];
}
void del(int x)
{
    if(b[x]==1) --s;
    --b[x];
}
int main()
{
    scanf("%d",&n);
    q=sqrt(n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].k=i;
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
        printf("%lld\n",c[i]);
    }
    return 0;
}