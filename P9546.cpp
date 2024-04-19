#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N];
struct str
{
    int s,ls,rs,w;
    friend str operator+(const str &a,const str &b)
    {
        if(a.s!=b.s) return a.s<b.s?a:b;
        str c;
        c.s=a.s,c.ls=a.ls,c.rs=b.rs,c.w=a.w+b.w;
        if((b.ls-a.rs)%2==0) c.w+=(b.ls-a.rs);
        else c.w+=(b.ls-a.rs)/2;
        return c;
    }
};
struct tree
{
    int l,r;
    str s;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[x<<1].s+T[x<<1|1].s;
}
void build(int x,int l,int r)
{
    T[x].l=l,T[x].r=r;
    if(l==r)
    {
        T[x].s.s=a[l];
        T[x].s.ls=T[x].s.rs=l;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(x);
}
void add(int x,int q,int k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s.s=k;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(x);
}
str sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r) return T[x].s;
    int z=T[x].l+T[x].r>>1;
    if(r<=z) return sum(x<<1,l,r);
    else if(l>z) return sum(x<<1|1,l,r);
    else return sum(x<<1,l,r)+sum(x<<1|1,l,r);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            add(1,x,k);
        }
        else if(z==2)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            str z=sum(1,l,r);
            if((r-l+1)%2==1&&z.s>0)
            {
                printf("%d\n",r-l+1);
                continue;
            }
            int w=z.w;
            if((z.ls+(r-l+1)-z.rs)%2==0) w+=(z.ls+(r-l+1)-z.rs);
            else w+=(z.ls+(r-l+1)-z.rs)/2;
            printf("%lld\n",w);
        }
    }
    return 0;
}