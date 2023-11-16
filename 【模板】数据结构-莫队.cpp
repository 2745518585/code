#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=2000001;
int n,m,q,s,a[N],b[N],c[N];
struct query
{
    int l,r,t;
}d[N];
bool cmp(query a,query b)
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
    --b[x];
    if(b[x]==0) --s;
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
        printf("%d\n",c[i]);
    }
    return 0;
}