#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,k,tot,d[N],e[N];
vector<int> a[N];
vector<pair<int,int>> c[N];
namespace sgt1
{
    int T[N];
    void add(int x,int k)
    {
        while(x>=1) T[x]+=k,x-=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x<=n) s+=T[x],x+=x&-x;
        return s;
    }
}
namespace sgt2
{
    struct tree
    {
        int l,r,s,k;
    }T[N<<2];
    void pushup(int x)
    {
        if(T[x<<1].s==T[x<<1|1].s) T[x].s=T[x<<1].s;
        else T[x].s=0;
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        T[x<<1].s=T[x<<1|1].s=T[x<<1].k=T[x<<1|1].k=T[x].k;
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s=T[x].k=0;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(l>r) return;
        if(T[x].l>=l&&T[x].r<=r&&T[x].s!=0)
        {
            sgt1::add(T[x].s,-(T[x].r-T[x].l+1));
            sgt1::add(k,T[x].r-T[x].l+1);
            T[x].s=T[x].k=k;
            return;
        }
        if(T[x].l==T[x].r)
        {
            sgt1::add(k,1);
            T[x].s=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
}
struct tree
{
    int f,d,b,bm;
}T[N];
struct str
{
    int d,b,t;
    str() {}
    str(int d,int b,int t):d(d),b(b),t(t) {}
    friend bool operator<(str a,str b)
    {
        if(a.d!=b.d) return a.d<b.d;
        else return a.b<b.b;
    }
}b[N];
void dfs(int x)
{
    T[x].b=++tot;
    T[x].d=T[T[x].f].d+1;
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
        T[i].f=x;
        dfs(i);
    }
    T[x].bm=tot;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d%d",&n,&k,&m);
        tot=0;
        for(int i=1;i<=n;++i) a[i].clear(),c[i].clear();
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        dfs(1);
        for(int i=1;i<=n;++i) b[i]=str(T[i].d,T[i].b,i);
        sort(b+1,b+n+1);
        for(int i=1;i<=m;++i)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            c[r].push_back(make_pair(l,i));
        }
        for(int i=1;i<=n;++i) sgt1::T[i]=0;
        sgt2::build(1,1,n);
        for(int i=1;i<=n;++i)
        {
            int x=i;
            d[0]=x;
            for(int j=1;j<=k;++j)
            {
                if(T[x].f!=0) x=T[x].f;
                d[j]=x;
            }
            for(int j=max(-k,-T[i].d+1);j<=k;++j)
            {
                int z=d[max((k-j)/2,0)];
                int l=lower_bound(b+1,b+n+1,str(T[i].d+j,T[z].b,0))-b,r=upper_bound(b+1,b+n+1,str(T[i].d+j,T[z].bm,0))-b-1;
                sgt2::add(1,l,r,i);
            }
            for(auto j:c[i])
            {
                e[j.second]=sgt1::sum(j.first);
            }
        }
        for(int i=1;i<=m;++i)
        {
            printf("%d\n",e[i]);
        }
    }
    return 0;
}