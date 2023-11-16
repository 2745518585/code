#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,q,a[N];
int dmin(int x,int y)
{
    if(x==0||y==0) return x+y;
    return a[x]<a[y]?x:y;
}
int dmax(int x,int y)
{
    if(x==0||y==0) return x+y;
    return a[x]>a[y]?x:y;
}
struct tree
{
    int l,r,s1,s2;
}T[N<<2];
void pushup(int x)
{
    T[x].s1=dmin(T[x<<1].s1,T[x<<1|1].s1);
    T[x].s2=dmax(T[x<<1].s2,T[x<<1|1].s2);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s1=T[x].s2=l;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q)
{
    if(T[x].l==T[x].r) return;
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q);
    else add(x<<1|1,q);
    pushup(x);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    q=unique(a+1,a+n+1)-a-1;
    build(1,1,q);
    while(true)
    {
        int z1=T[1].s1,z2=T[1].s2;
        if(a[z1]==a[z2]) break;
        if(a[z2]-a[z1]<=a[z1]) a[z2]-=a[z1];
        else a[z2]=a[z2]%a[z1]+a[z1];
        add(1,z2);
    }
    printf("%d",a[1]);
    return 0;
}