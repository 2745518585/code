#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
struct tree
{
    int l,r,s1,s2;
}T[N<<2];
void pushup(int x)
{
    T[x].s1=min(T[x<<1].s1,T[x<<1|1].s1);
    T[x].s2=max(T[x<<1].s2,T[x<<1|1].s2);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s1=T[x].s2=a[l];
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
int sum1(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s1;
    }
    int z=T[x].l+T[x].r>>1,s=1e9;
    if(l<=z) s=min(s,sum1(x<<1,l,r));
    if(r>z) s=min(s,sum1(x<<1|1,l,r));
    return s;
}
int sum2(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s2;
    }
    int z=T[x].l+T[x].r>>1,s=0;
    if(l<=z) s=max(s,sum2(x<<1,l,r));
    if(r>z) s=max(s,sum2(x<<1|1,l,r));
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        build(1,1,n);
        int x=1,y=n;
        while(x<=y)
        {
            if(a[x]==sum1(1,x,y)||a[x]==sum2(1,x,y)) ++x;
            else if(a[y]==sum1(1,x,y)||a[y]==sum2(1,x,y)) --y;
            else break;
        }
        if(x>y) printf("-1\n");
        else printf("%d %d\n",x,y);
    }
    return 0;
}