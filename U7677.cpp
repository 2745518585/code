#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,b[N];
ll T[N],s;
struct str
{
    int x,k;
}a[N];
struct str2
{
    int l,r,k;
}d1[N],d2[N];
bool cmp(str a,str b)
{
    if(a.k!=b.k) return a.k<b.k;
    return a.x<b.x;
}
bool cmp1(str2 a,str2 b)
{
    if(a.l!=b.l) return a.l<b.l;
    return a.r<b.r;
}
bool cmp2(str2 a,str2 b)
{
    if(a.r!=b.r) return a.r<b.r;
    return a.l<b.l;
}
void add(int x,int k)
{
    T[x]+=k;
    while(x<=n)
    {
        x+=(x&(-x));
        T[x]+=k;
    }
}
ll sum(int x)
{
    ll s=T[x];
    while(x!=0)
    {
        x-=(x&(-x));
        s+=T[x];
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].k);
        a[i].x=i;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i) b[a[i].x]=i;
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d1[i].l,&d1[i].r);
        d1[i].k=i;
        d2[i]=d1[i];
    }
    sort(d1+1,d1+m+1,cmp1);
    sort(d2+1,d2+m+1,cmp2);
    a[0].k=-1e9,a[n+1].k=1e9;
    int x1=1,x2=1;
    while(d1[x1].l==1) ++x1;
    for(int i=1;i<=n;++i)
    {
        if(b[i]!=1&&a[b[i]].k-a[b[i]-1].k<=a[b[i]+1].k-a[b[i]].k)
        {
            add(a[b[i]-1].x,1);
        }
        if(b[i]!=n&&a[b[i]+1].k-a[b[i]].k<=a[b[i]].k-a[b[i]-1].k)
        {
            add(a[b[i]+1].x,1);
        }
        while(x1<=m&&d1[x1].l-1==i)
        {
            s-=(ll)(sum(d1[x1].r)-sum(d1[x1].l-1))*d1[x1].k;
            ++x1;
        }
        while(x2<=m&&d2[x2].r==i)
        {
            s+=(ll)(sum(d2[x2].r)-sum(d2[x2].l-1))*d2[x2].k;
            ++x2;
        }
    }
    printf("%lld",s);
    return 0;
}