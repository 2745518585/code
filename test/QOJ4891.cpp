#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T> inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
template<typename T,typename ...O> inline void read(T &x,O &...o) {read(x),read(o...);}
template<typename T> inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
template<typename T,typename ...O> inline void print(T x,O ...o) {print(x),putchar(' '),print(o...);}
const int N=1000001,M=21;
int n1,n,m,q,b1[N],b[N],f[N],g[N][M],rt[N];
bool h[N];
vector<int> a1[N],a[N],e[N];
vector<pair<int,int>> v[N];
vector<pair<int,pair<int,int>>> d[N];
struct
{
    int x1,x2,d1,d2;
}c[N];
namespace sgt
{
    int tot;
    struct tree
    {
        int l,r,s;
    }T[N<<4];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s;
    }
    void add(int &x,int ls,int rs,int q,int k)
    {
        T[++tot]=T[x],x=tot;
        if(ls==rs)
        {
            T[x].s+=k;
            return;
        }
        int z=ls+rs>>1;
        if(q<=z) add(T[x].l,ls,z,q,k);
        else add(T[x].r,z+1,rs,q,k);
        pushup(x);
    }
    int sum(int x,int ls,int rs,int l,int r)
    {
        if(ls>=l&&rs<=r) return T[x].s;
        int z=ls+rs>>1,s=0;
        if(l<=z) s+=sum(T[x].l,ls,z,l,r);
        if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
        return s;
    }
    int merge(int x1,int x2,int ls,int rs)
    {
        if(x1==0||x2==0) return x1|x2;
        T[++tot]=T[x1],x1=tot;
        if(ls==rs)
        {
            T[x1].s+=T[x2].s;
            return x1;
        }
        int z=ls+rs>>1;
        T[x1].l=merge(T[x1].l,T[x2].l,ls,z);
        T[x1].r=merge(T[x1].r,T[x2].r,z+1,rs);
        pushup(x1);
        return x1;
    }
}
struct tree
{
    int f,s,d,z;
}T1[N],T[N];
void dfs0(int x)
{
    T1[x].d=T1[T1[x].f].d+1;
    for(auto i:a1[x])
    {
        if(i==T1[x].f) continue;
        T1[i].f=x;
        dfs0(i);
    }
}
void dfs1(int x)
{
    T[x].s=1;
    T[x].d=T[T[x].f].d+1;
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
        T[i].f=x;
        dfs1(i);
        T[x].s+=T[i].s;
        if(T[i].s>T[T[x].z].s) T[x].z=i;
    }
}
void dfs2(int x,int p,int t)
{
    d[p].push_back(make_pair(b1[x],make_pair(x,t)));
    v[t].push_back(make_pair(x,b1[x]));
    for(auto i:a1[x])
    {
        if(i==T1[x].f) continue;
        dfs2(i,p,t);
    }
}
void dfs(int x)
{
    vector<pair<int,int>> p;
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        dfs(i);
        for(auto j:e[i])
        {
            p.push_back(make_pair(j,f[j]));
            f[j]=n+1;
        }
    }
    if(T[x].z)
    {
        dfs(T[x].z);
        swap(e[x],e[T[x].z]);
        rt[x]=rt[T[x].z];
    }
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        rt[x]=sgt::merge(rt[x],rt[i],1,n);
    }
    sgt::add(rt[x],1,n,T[x].d,1);
    auto add=[&](int t,int d)
    {
        if(f[t]==n+1)
        {
            e[x].push_back(t);
            f[t]=d;
        }
        else
        {
            if(d<f[t])
            {
                sgt::add(rt[x],1,n,f[t],-1);
                f[t]=d;
            }
            else sgt::add(rt[x],1,n,d,-1);
        }
    };
    add(b[x],T[x].d);
    for(auto i:p) add(i.first,i.second);
    for(auto i:d[x])
    {
        g[i.second.second][i.second.first]=f[i.first];
    }
}
int main()
{
    read(n1,n,q);
    for(int i=1;i<=n1-1;++i)
    {
        int x,y;
        read(x,y);
        a1[x].push_back(y);
        a1[y].push_back(x);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        read(x,y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for(int i=1;i<=n1;++i) read(b1[i]);
    for(int i=1;i<=n;++i) read(b[i]);
    dfs0(1);
    dfs1(1);
    for(int i=1;i<=q;++i)
    {
        int z;
        read(z);
        if(z==1)
        {
            ++m;
            read(c[m].x1,c[m].x2,c[m].d1,c[m].d2);
            dfs2(c[m].x1,c[m].x2,m);
        }
        else if(z==2)
        {
            int x,k;
            read(x,k);
            b1[x]=k;
        }
    }
    for(int i=1;i<=n;++i) f[i]=n+1;
    dfs(1);
    int las=0;
    for(int i=1;i<=m;++i)
    {
        c[i].d1^=las,c[i].d2^=las;
        int s=sgt::sum(rt[c[i].x2],1,n,T[c[i].x2].d,T[c[i].x2].d+c[i].d2);
        for(auto j:v[i])
        {
            if(h[j.second]==false&&T1[j.first].d<=T1[c[i].x1].d+c[i].d1&&(g[i][j.first]==n+1||g[i][j.first]>T[c[i].x2].d+c[i].d2))
            {
                h[j.second]=true;
                ++s;
            }
        }
        for(auto j:v[i]) h[j.second]=false;
        print(las=s);
        putchar('\n');
    }
    return 0;
}