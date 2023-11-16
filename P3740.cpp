#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000;
int m,n,s,a[N+1][2],b[N<<1+1];
bool h[N+1];
struct tree
{
    int l,r,k;
}T[N<<3+1];
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r,T[x].k=0;
    if(l==r) return;
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
}
void add(int x,int l,int r,int k)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        T[x].k=k;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(l<=z) add(x<<1,l,r,k);
    if(r>z) add(x<<1|1,l,r,k);
}
int find(int x,int q)
{
    if(T[x].l==T[x].r) return T[x].k;
    int z=T[x].l+T[x].r>>1;
    if(q<=z) return max(T[x].k,find(x<<1,q));
    else return max(T[x].k,find(x<<1|1,q));
}
int main()
{
    scanf("%d%d",&n,&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i][0],&a[i][1]);
        b[i*2-1]=a[i][0];
        b[i*2]=a[i][1];
    }
    sort(b+1,b+n*2+1);
    m=unique(b+1,b+n*2+1)-(b+1);
    for(int i=1;i<=m-1;++i)
    {
        b[m+i]=(b[i]+b[i+1]>>1);
    }
    sort(b+1,b+m*2);
    m=unique(b+1,b+m*2)-(b+1);
    build(1,1,m);
    for(int i=1;i<=n;++i)
    {
        add(1,lower_bound(b+1,b+m+1,a[i][0])-b,lower_bound(b+1,b+m+1,a[i][1])-b,i);
    }
    for(int i=1;i<=m;++i)
    {
        h[find(1,i)]=true;
    }
    for(int i=1;i<=n;++i) s+=h[i];
    printf("%d",s);
    return 0;
}