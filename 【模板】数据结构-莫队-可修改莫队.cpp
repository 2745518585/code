#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=2000001;
int n,m,m1,m2,q,s,l,r,k,a[N],b[N],c[N];
struct query
{
    int l,r,k,t;
}d[N];
struct change
{
    int x,a;
}e[N];
bool cmp(query a,query b)
{
    if((a.l-1)/q!=(b.l-1)/q) return a.l<b.l;
    if((a.r-1)/q!=(b.r-1)/q) return a.r<b.r;
    return a.k<b.k;
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
void upd(int x)
{
    if(l<=e[x].x&&r>=e[x].x)
    {
        del(a[e[x].x]);
        add(e[x].a);
    }
    swap(a[e[x].x],e[x].a);
}
int main()
{
    scanf("%d%d",&n,&m);
    q=pow(n,(double)2/3);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='Q')
        {
            ++m1;
            scanf("%d%d",&d[m1].l,&d[m1].r);
            d[m1].k=m2;
            d[m1].t=m1;
        }
        else
        {
            ++m2;
            scanf("%d%d",&e[m2].x,&e[m2].a);
        }
    }
    sort(d+1,d+m1+1,cmp);
    l=1,r=0,k=0;
    for(int i=1;i<=m1;++i)
    {
        while(l>d[i].l) add(a[--l]);
        while(r<d[i].r) add(a[++r]);
        while(l<d[i].l) del(a[l++]);
        while(r>d[i].r) del(a[r--]);
        while(k<d[i].k) upd(++k);
        while(k>d[i].k) upd(k--);
        c[d[i].t]=s;
    }
    for(int i=1;i<=m1;++i)
    {
        printf("%d\n",c[i]);
    }
    return 0;
}