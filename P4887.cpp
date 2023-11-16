#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,k,t,a[N],f[N],g[N],h[N];
ll c[N],p[N];
struct str
{
    int l,r,k;
}d[N];
struct str2
{
    int l,r,u,t;
};
vector<str2> e[N];
bool cmp(str a,str b)
{
    if((a.l-1)/q!=(b.l-1)/q) return a.l<b.l;
    return a.r<b.r;
}
int sum(int x)
{
    int s=0;
    while(x!=0) x^=(x&-x),++s;
    return s;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    q=sqrt(n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<=16383;++i)
    {
        if(sum(i)==k) g[++t]=i;
    }
    for(int i=1;i<=n;++i)
    {
        f[i]=h[a[i]];
        for(int j=1;j<=t;++j) ++h[a[i]^g[j]];
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].k=i;
    }
    sort(d+1,d+m+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;++i)
    {
        if(l<d[i].l) e[r].push_back((str2){l,d[i].l-1,-1,i});
        while(l<d[i].l) ++l,c[i]+=f[l-1];
        if(l>d[i].l) e[r].push_back((str2){d[i].l,l-1,1,i});
        while(l>d[i].l) c[i]-=f[l-1],--l;
        if(r<d[i].r) e[l-1].push_back((str2){r+1,d[i].r,-1,i});
        while(r<d[i].r) ++r,c[i]+=f[r];
        if(r>d[i].r) e[l-1].push_back((str2){d[i].r+1,r,1,i});
        while(r>d[i].r) c[i]-=f[r],--r;
    }
    for(int i=0;i<=16383;++i) h[i]=0;
    for(int i=1;i<=n;++i)
    {
        f[i]=h[a[i]];
        for(int j=1;j<=t;++j) ++h[a[i]^g[j]];
        for(int j=0;j<e[i].size();++j)
        {
            for(int l=e[i][j].l;l<=e[i][j].r;++l)
            {
                c[e[i][j].t]+=e[i][j].u*(h[a[l]]-(k==0&&l<=i));
            }
        }
    }
    for(int i=1;i<=m;++i) c[i]+=c[i-1];
    for(int i=1;i<=m;++i) p[d[i].k]=c[i];
    for(int i=1;i<=m;++i)
    {
        printf("%lld\n",p[i]);
    }
    return 0;
}