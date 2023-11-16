#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001;
int m,n,k,b[N],q,f[N];
struct str
{
    int x,y,k;
}a[N];
struct Segment_tree
{
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
        if(l==r)
        {
            T[x].s=0;
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
}T;
bool cmp(str a,str b)
{
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}
int main()
{
    scanf("%d%d%d",&m,&n,&k);
    for(int i=1;i<=k;++i)
    {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].k);
        b[i]=a[i].y;
    }
    sort(b+1,b+k+1);
    q=unique(b,b+k+1)-b-1;
    sort(a+1,a+k+1,cmp);
    T.build(1,1,q);
    int s=0;
    for(int i=1;i<=k;++i)
    {
    	int y=lower_bound(b+1,b+q+1,a[i].y)-b;
        f[i]=T.sum(1,1,y)+a[i].k;
        T.add(1,y,f[i]);
        s=max(s,f[i]);
    }
    printf("%d",s);
    return 0;
}
