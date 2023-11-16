#include<cstdio>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
const int N=1000001;
int n,m,a[N],b[N],c[N],d[N][2],f[N],g[N];
vector<int> e[N];
struct tree
{
    int l,r,s,k;
}T[N<<2];
void pushup(int x)
{
    T[x].s=min(T[x<<1].s,T[x<<1|1].s);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].s+=T[x].k;
    T[x<<1].k+=T[x].k;
    T[x<<1|1].s+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k=0;
    if(l==r)
    {
        T[x].s=g[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(l>r) return;
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].s+=k;
        T[x].k+=k;
        return;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
    pushup(x);
}
int sum(int x,int l,int r)
{
    if(l>r) return 1e9;
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1,s=1e9;
    if(l<=z) s=min(s,sum(x<<1,l,r));
    if(r>z) s=min(s,sum(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    a[1]=0;
    for(int i=2;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        d[i][0]=lower_bound(a+1,a+n+1,a[i]-x)-a;
        d[i][1]=upper_bound(a+1,a+n+1,a[i]+x)-a-1;
        e[d[i][1]+1].push_back(i);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&c[i]);
    }
    for(int i=1;i<=n+1;++i) g[i]=1e9;
    g[0]=0;
    int s=1e9;
    for(int i=1;i<=m+1;++i)
    {
        build(1,0,n);
        for(int j=1;j<=n+1;++j)
        {
            for(auto k:e[j])
            {
                add(1,0,d[k][0]-1,c[k]);
            }
            f[j]=sum(1,0,j-1)+b[j];
        }
        for(int j=1;j<=n+1;++j) g[j]=f[j];
        s=min(s,f[n+1]);
    }
    printf("%d",s);
    return 0;
}