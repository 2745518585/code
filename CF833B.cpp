#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;
const int N=50001,M=51;
int n,m,a[N],b[N],c[N],f[M][N];
struct tree
{
    int l,r,k;
    int s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=max(T[x<<1].s,T[x<<1|1].s);
}
void pushdown(int x)
{
    if(T[x].k==0) return;
    T[x<<1].k+=T[x].k;
    T[x<<1].s+=T[x].k;
    T[x<<1|1].k+=T[x].k;
    T[x<<1|1].s+=T[x].k;
    T[x].k=0;
}
void build(int x,int l,int r,int t)
{
    T[x].l=l;
    T[x].r=r;
    T[x].k=0;
    if(l==r)
    {
        T[x].s=f[t][l-1];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z,t);
    build(x<<1|1,z+1,r,t);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k+=k;
        T[x].s+=k;
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
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    pushdown(x);
    int z=T[x].l+T[x].r>>1,s=0;
    if(l<=z) s=max(s,sum(x<<1,l,r));
    if(r>z) s=max(s,sum(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=c[a[i]];
        c[a[i]]=i;
    }
    for(int i=1;i<=m;++i)
    {
        build(1,1,n+1,i-1);
        for(int j=1;j<=n;++j)
        {
            add(1,b[j]+1,j,1);
            f[i][j]=sum(1,1,j+1);
        }
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        s=max(s,f[m][i]);
    }
    printf("%d",s);
    return 0;
}