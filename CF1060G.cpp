#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,b[N],d1[N],d2[N];
ll g[N];
pair<int,int> h[N];
struct str
{
    int x,y,t;
    str() {}
    str(int x,int y,int t):x(x),y(y),t(t) {}
}a[N];
namespace sgt
{
    struct tree
    {
        int l,r,s;
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
            T[x].s=1;
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
            T[x].s=k;
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        int z=T[x].l+T[x].r>>1,s=0;
        if(l<=z) s+=sum(x<<1,l,r);
        if(r>z) s+=sum(x<<1|1,l,r);
        return s;
    }
    int find(int x,int k)
    {
        if(T[x].l==T[x].r) return T[x].l;
        int z=T[x].l+T[x].r>>1;
        if(k<=T[x<<1].s) return find(x<<1,k);
        else return find(x<<1|1,k-T[x<<1].s);
    }
}
bool cmp(str a,str b)
{
    if(a.x!=b.x) return a.x<b.x;
    return a.t<b.t;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        a[++q]=str(b[i],0,0);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d1[i],&d2[i]);
        a[++q]=str(d1[i],0,i);
    }
    sort(a+1,a+q+1,cmp);
    sgt::build(1,1,n);
    int x=2e9,w=n,t=0;
    for(int i=q;i>=1;--i)
    {
        if(w==0) break;
        if(a[i].x<x)
        {
            int z=(x-a[i].x-1)/w+1;
            x-=z*w,t+=z;
            // printf("[%d %d]\n",x,x+w-1);
        }
        int z=sgt::find(1,a[i].x-x+1);
        if(a[i].t==0) sgt::add(1,z,0),--w;
        else
        {
            h[a[i].t]=make_pair(z,t);
        }
    }
    for(int i=1;i<=m;++i)
    {
        a[i]=str(h[i].second-d2[i],h[i].first,i);
    }
    sort(a+1,a+m+1,cmp);
    sgt::build(1,1,n);
    x=2e9,w=n,t=0;
    int p=1;
    for(int i=n;i>=1;--i)
    {
        if(w==0) break;
        if(b[i]<x)
        {
            int z=(x-b[i]-1)/w+1;
            x-=z*w,t+=z;
        }
        while(p<=m&&a[p].x<=t)
        {
            g[a[p].t]=x+(ll)(t-a[p].x)*w+sgt::sum(1,1,a[p].y)-1;
            ++p;
        }
        sgt::add(1,sgt::find(1,b[i]-x+1),0),--w;
    }
    for(int i=1;i<=m;++i)
    {
        if(d1[i]<b[1]) printf("%lld\n",d1[i]);
        else printf("%lld\n",g[i]);
    }
    return 0;
}