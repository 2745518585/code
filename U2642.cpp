#include<bits/stdc++.h>
using namespace std;
const int N=2000001,M=11;
struct tree
{
    int l,r,s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=max(T[x<<1].s,T[x<<1|1].s);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].s=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=max(T[x].s,k);
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1,s=0;
    if(l<=z) s=max(s,sum(x<<1,l,r));
    if(r>z) s=max(s,sum(x<<1|1,l,r));
    return s;
}
int n,m,q,a[N],b[N],c[N],pow4[M],h[N];
vector<int> g[N];
struct str
{
    int l,r,k;
}f[N*M];
struct str2
{
    int l,r,k;
}d[N];
bool cmp(str2 a,str2 b)
{
    return a.r<b.r;
}
void init()
{
    pow4[0]=1;
    for(int i=1;i<=10;++i) pow4[i]=pow4[i-1]*4;
}
int main()
{
    init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i) g[i].push_back(0);
    for(int i=1;i<=n;++i)
    {
        b[i]=++h[a[i]];
        g[a[i]].push_back(i);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=0;pow4[j]<=b[i];++j)
        {
            f[++q]=(str){g[a[i]][b[i]-pow4[j]+1],i,pow4[j]};
        }
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].k=i;
    }
    sort(d+1,d+m+1,cmp);
    build(1,1,n);
    int x1=0,x2=0;
    for(int i=1;i<=n;++i)
    {
        while(f[x1+1].r==i)
        {
            ++x1;
            add(1,f[x1].l,f[x1].k);
        }
        while(d[x2+1].r==i)
        {
            ++x2;
            c[d[x2].k]=sum(1,d[x2].l,i);
        }
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",c[i]*2);
    }
    return 0;
}