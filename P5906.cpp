#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=500001;
int n,m,q,k,a[N],b1[N],b2[N],b3[N],b4[N],c[N],e[N],s;
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
    b3[a[x]]=b1[a[x]]=max(b1[a[x]],x);
    b4[a[x]]=b2[a[x]]=min(b2[a[x]],x);
    s=max(s,b1[a[x]]-b2[a[x]]);
}
void add2(int x)
{
    b1[a[x]]=max(b1[a[x]],x);
    b2[a[x]]=min(b2[a[x]],x);
    s=max(s,b1[a[x]]-b2[a[x]]);
}
void del(int x)
{
    b1[a[x]]=b3[a[x]];
    b2[a[x]]=b4[a[x]];
}
void init()
{
    for(int i=1;i<=k;++i)
    {
        b1[i]=b3[i]=0;
        b2[i]=b4[i]=1e9;
    }
}
int main()
{
    scanf("%d",&n);
    q=sqrt(n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        e[i]=a[i];
    }
    sort(e+1,e+n+1);
    k=unique(e,e+n+1)-e-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(e+1,e+k+1,a[i])-e;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].k=i;
    }
    sort(d+1,d+m+1,cmp);
    d[0].l=-1e9;
    init();
    int l=1,r=0,s0=0;
    for(int i=1;i<=m;++i)
    {
        if((d[i].l-1)/q!=(d[i-1].l-1)/q)
        {
            init();
            l=(d[i].l-1)/q*q+q,r=l-1;
            s0=0;
        }
        if((d[i].l-1)/q==(d[i].r-1)/q)
        {
            s=0;
            for(int j=d[i].l;j<=d[i].r;++j) add2(j);
            for(int j=d[i].l;j<=d[i].r;++j)
            {
                b1[a[j]]=b3[a[j]]=0;
                b2[a[j]]=b4[a[j]]=1e9;
            }
            c[d[i].k]=s;
            continue;
        }
        while(l<(d[i].l-1)/q*q+q) del(l++);
        s=s0;
        while(d[i].r>r) add(++r);
        s0=s;
        while(d[i].l<l) add2(--l);
        c[d[i].k]=s;
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",c[i]);
    }
    return 0;
}