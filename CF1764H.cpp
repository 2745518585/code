#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3000001;
int n,m,q,o,k,f[N],g[N],h[N];
ll d[N],T[N];
struct str
{
    int l,r,t;
    str(){}
    str(int l,int r,int t):l(l),r(r),t(t){}
    friend bool operator <(str a,str b)
    {
        return a.l<b.l;
    }
}a[N],b[N],c[N];
set<str> Set;
bool cmp(str a,str b)
{
    return a.l<b.l;
}
void add(int x,int k)
{
    while(x<=m)
    {
        T[x]+=k;
        x+=(x&-x);
    }
}
ll sum(int x)
{
    ll s=0;
    while(x>=1)
    {
        s+=T[x];
        x-=(x&-x);
    }
    return s;
}
int main()
{
    scanf("%d%d%d",&n,&m,&o);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&a[i].l,&a[i].r);
        a[m+i]=a[i];
    }
    q=m;
    m<<=1;
    for(int i=1;i<=q;++i) b[i].l=i,b[i].r=i+o-1,b[i].t=i;
    Set.insert(str(1,n,0));
    for(int i=1;i<=m;++i)
    {
        set<str>::iterator p,p2,ps;
        p=Set.upper_bound(str(a[i].l,0,0)),ps=--Set.upper_bound(str(a[i].r,0,0));
        p2=p,p2--;
        str z1=(*p2),z2=z1;
        f[i]=z1.t;
        if(z1.r>=a[i].r)
        {
            g[z1.t]=max(g[z1.t],i);
            Set.erase(p2);
            if(z1.l<a[i].l) Set.insert(str(z1.l,a[i].l-1,z1.t));
            if(z1.r>a[i].r) Set.insert(str(a[i].r+1,z1.r,z1.t));
            Set.insert(str(a[i].l,a[i].r,i));
            if(z1.t+1<=i-1) c[++k]=str(z1.t+1,i-1,a[i].r-a[i].l+1);
            continue;
        }
        Set.erase(p2);
        while(p!=ps)
        {
            g[(*p).t]=max(g[(*p).t],i);
            if((*p).t+1<=i-1) c[++k]=str((*p).t+1,i-1,(*p).r-(*p).l+1);
            p2=p++;
            Set.erase(p2);
        }
        z1=*ps;
        Set.erase(ps);
        g[z2.t]=max(g[z2.t],i);
        g[z1.t]=max(g[z1.t],i);
        if(z2.t+1<=i-1) c[++k]=str(z2.t+1,i-1,z2.r-a[i].l+1);
        if(z1.t+1<=i-1) c[++k]=str(z1.t+1,i-1,a[i].r-z1.l+1);
        if(z2.l<a[i].l) Set.insert(str(z2.l,a[i].l-1,z2.t));
        if(z1.r>a[i].r) Set.insert(str(a[i].r+1,z1.r,z1.t));
        Set.insert(str(a[i].l,a[i].r,i));
    }
    for(set<str>::iterator p=Set.begin();p!=Set.end();++p)
    {
        if((*p).t+1<=m) c[++k]=str((*p).t+1,m,(*p).r-(*p).l+1);
        g[(*p).t]=max(g[(*p).t],m+1);
    }
    for(int i=m;i>=1;--i)
    {
        h[i]=max(h[i],g[i]);
        if(f[i]) h[f[i]]=max(h[f[i]],h[i]);
    }
    sort(b+1,b+q+1,cmp);
    sort(c+1,c+k+1,cmp);
    int x=1;
    for(int i=1;i<=q;++i)
    {
        while(x<=k&&c[x].l<=b[i].l)
        {
            add(m-c[x].r+1,c[x].t);
            ++x;
        }
        d[b[i].t]+=sum(m-b[i].r+1);
    }
    k=0;
    for(int i=1;i<=m;++i)
    {
        if(f[i]<i&&h[i]>i)
        {
            c[++k]=str(f[i]+1,i,1);
            c[++k]=str(f[i]+1,h[i],-1);
            c[++k]=str(i+1,i,-1);
            c[++k]=str(i+1,h[i],1);
        }
    }
    sort(c+1,c+k+1,cmp);
    for(int i=1;i<=m;++i) T[i]=0;
    x=1;
    for(int i=1;i<=q;++i)
    {
        while(x<=k&&c[x].l<=b[i].l)
        {
            add(c[x].r,c[x].t);
            ++x;
        }
        d[b[i].t]+=sum(b[i].r);
    }
    for(int i=1;i<=q;++i)
    {
        printf("%lld ",d[i]);
    }
    return 0;
}