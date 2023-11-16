#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=2000001;
int n,m,q,k,s,sx,a[N],ua[N],b1[N],b2[N],b1x[N],b2x[N],c[N];
struct query
{
    int l,r,t;
}d[N];
bool cmp(query a,query b)
{
    if((a.l-1)/q!=(b.l-1)/q) return a.l<b.l;
    return a.r<b.r;
}
void add(int x,bool u)
{
    b1[a[x]]=min(b1[a[x]],x);
    b2[a[x]]=max(b2[a[x]],x);
    s=max(s,b2[a[x]]-b1[a[x]]);
    if(u) b1x[a[x]]=b1[a[x]],b2x[a[x]]=b2[a[x]],sx=s;
}
void del(int x)
{
    b1[a[x]]=b1x[a[x]];
    b2[a[x]]=b2x[a[x]];
    s=sx;
}
int main()
{
    scanf("%d",&n);
    q=sqrt(n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        ua[i]=a[i];
    }
    sort(ua+1,ua+n+1);
    k=unique(ua+1,ua+n+1)-ua-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(ua+1,ua+k+1,a[i])-ua;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].t=i;
    }
    sort(d+1,d+m+1,cmp);
    d[0].l=-1e9;
    int l=1,r=0;
    for(int i=1;i<=m;++i)
    {
        if((d[i].l-1)/q!=(d[i-1].l-1)/q)
        {
            for(int i=1;i<=k;++i) b1[i]=b1x[i]=1e9,b2[i]=b2x[i]=0;
            s=sx=0;
            l=(d[i].l-1)/q*q+q,r=l-1;
        }
        if((d[i].l-1)/q==(d[i].r-1)/q)
        {
            for(int j=d[i].l;j<=d[i].r;++j) add(j,false);
            c[d[i].t]=s;
            for(int j=d[i].l;j<=d[i].r;++j) del(j);
            continue;
        }
        while(r<d[i].r) add(++r,true);
        while(l>d[i].l) add(--l,false);
        c[d[i].t]=s;
        while(l<(d[i].l-1)/q*q+q) del(l++);
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",c[i]);
    }
    return 0;
}