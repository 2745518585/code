#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
const int N=1000001;
int n,m,q,a[N],b2[N][3],d[N],e[N],T[N],fa[N];
struct str
{
    int l,r;
    str(){}
    str(int l,int r):l(l),r(r){}
};
vector<str> b[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
bool cmp(str a,str b)
{
    return a.l>b.l;
}
namespace sgt1
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=q) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}
namespace sgt2
{
    struct str
    {
        int x,s;
        str(){}
        str(int x,int s):x(x),s(s){}
        friend bool operator<(str a,str b)
        {
            if(a.s!=b.s) return a.s<b.s;
            return a.x<b.x;
        }
    };
    struct tree
    {
        int l,r,k;
        str s;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=min(T[x<<1].s,T[x<<1|1].s);
    }
    void pushdown(int x)
    {
        if(T[x].k==0) return;
        T[x<<1].k+=T[x].k;
        T[x<<1].s.s+=T[x].k;
        T[x<<1|1].k+=T[x].k;
        T[x<<1|1].s.s+=T[x].k;
        T[x].k=0;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        T[x].k=0;
        if(l==r)
        {
            T[x].s=str(l,0);
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
            T[x].k+=k;
            T[x].s.s+=k;
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
    str sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            return T[x].s;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        str s(0,1e9);
        if(l<=z) s=min(s,sum(x<<1,l,r));
        if(r>z) s=min(s,sum(x<<1|1,l,r));
        return s;
    }
}
int main()
{
    int T;
    read(T);
    while(T--)
    {
        read(n),read(m);
        q=0;
        for(int i=1;i<=m;++i)
        {
            read(b2[i][0]),read(b2[i][1]),read(b2[i][2]);
            e[++q]=b2[i][2];
        }
        e[++q]=0;
        sort(e+1,e+q+1);
        q=unique(e+1,e+q+1)-e-1;
        for(int i=1;i<=q;++i) b[i].clear();
        for(int i=1;i<=m;++i)
        {
            b[lower_bound(e+1,e+q+1,b2[i][2])-e].push_back(str(b2[i][0],b2[i][1]));
        }
        for(int i=1;i<=n;++i) fa[i]=i,a[i]=0,d[i]=1;
        fa[n+1]=n+1;
        bool u=false;
        for(int i=q;i>=1;--i)
        {
            sort(b[i].begin(),b[i].end(),cmp);
            int z=n+1;
            for(auto j:b[i])
            {
                if(j.r<z)
                {
                    if(find(j.l)>j.r)
                    {
                        u=true;
                        break;
                    }
                    z=find(j.l);
                    a[z]=i;
                }
            }
            if(u) break;
            for(auto j:b[i])
            {
                int x=find(j.l);
                while(x<=j.r) d[x]=i,fa[x]=x+1,x=find(x);
            }
        }
        if(u)
        {
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=q;++i) sgt1::T[i]=0;
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i]!=0)
            {
                s+=sgt1::sum(q)-sgt1::sum(a[i]);
                sgt1::add(a[i],1);
            }
        }
        sgt2::build(1,1,q);
        for(int i=1;i<=n;++i)
        {
            if(a[i]!=0) sgt2::add(1,a[i]+1,q,1);
        }
        for(int i=1;i<=n;++i)
        {
            if(a[i]!=0)
            {
                sgt2::add(1,a[i]+1,q,-1);
                sgt2::add(1,1,a[i]-1,1);
            }
            else
            {
                sgt2::str x=sgt2::sum(1,d[i],q);
                s+=x.s;
                sgt2::add(1,1,x.x-1,1);
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}