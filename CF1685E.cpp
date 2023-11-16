#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,n2,m,a[N],b[N];
struct Segment_tree
{
    struct num
    {
        int x,s;
        num() {}
        num(int x,int s):x(x),s(s) {}
        friend num min(num a,num b)
        {
            return a.s<b.s?a:b;
        }
    };
    struct tree
    {
        int l,r,k;
        num s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=min(T[x<<1].s,T[x<<1|1].s);
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        T[x<<1].s.s+=T[x].k;
        T[x<<1].k+=T[x].k;
        T[x<<1|1].s.s+=T[x].k;
        T[x<<1|1].k+=T[x].k;
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        if(l==r)
        {
            T[x].s=num(l,0);
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s.s+=k;
            T[x].k+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
    num sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        num s=num(0,1e9);
        if(l<=z) s=min(s,sum(x<<1,l,r));
        if(r>z) s=min(s,sum(x<<1|1,l,r));
        return s;
    }
}Tree;
struct num
{
    int c[N],l,r,s;
    void add(int x)
    {
        if(x<l||x>r) return;
        if(x-1>=l)
        {
            s-=c[x-1];
            c[x-1]=((b[x]-b[x-1])%n+n)%n;
            s+=c[x-1];
        }
        if(x<=r-1)
        {
            s-=c[x];
            c[x]=((b[x+1]-b[x])%n+n)%n;
            s+=c[x];
        }
        s-=c[0];
        c[0]=((b[l]-b[r])%n+n)%n;
        s+=c[0];
    }
    bool check()
    {
        return s==n;
    }
}sum1,sum2;
int sum(int x)
{
    if(x>n2) return 1;
    if(x<n2) return -1;
    return 0;
}
int main()
{
    scanf("%d%d",&n,&m);
    n2=n+1;
    n=n*2+1;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[a[i]]=i;
    }
    Tree.build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        Tree.add(1,i,n,sum(a[i]));
    }
    a[n+1]=a[1];
    sum1.l=1,sum1.r=n2;
    sum2.l=n2,sum2.r=n;
    for(int i=1;i<=n2;++i) sum1.add(i);
    for(int i=n2;i<=n;++i) sum2.add(i);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        swap(a[x],a[y]);
        b[a[x]]=x,b[a[y]]=y;
        Tree.add(1,x,n,sum(a[x])-sum(a[y]));
        Tree.add(1,y,n,sum(a[y])-sum(a[x]));
        sum1.add(a[x]),sum1.add(a[y]);
        sum2.add(a[x]),sum2.add(a[y]);
        if(Tree.sum(1,b[n2]-1,b[n2]-1).s!=Tree.T[1].s.s)
        {
            printf("%d\n",(Tree.T[1].s.x)%n);
            continue;
        }
        if(!sum2.check())
        {
            printf("%d\n",(b[n2]-1)%n);
            continue;
        }
        if(!sum1.check())
        {
            printf("%d\n",b[n2]%n);
            continue;
        }
        printf("-1\n");
    }
    return 0;
}