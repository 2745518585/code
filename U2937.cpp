#include<bits/stdc++.h>
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
template<typename T>
inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
const int N=1000001;
int n,m,q,w,p=1,tot,t[N],rt[N],f[N];
vector<int> b[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
struct tree
{
    int d,b,bm;
}T[N];
namespace Segment_tree
{
    int tot;
    struct tree
    {
        int l,r;
        ll s;
    }T[N<<4];
    void pushup(int x)
    {
        T[x].s=T[T[x].l].s+T[T[x].r].s;
    }
    void add(int &x,int ls,int rs,int q,int k)
    {
        T[++tot]=T[x];
        x=tot;
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
    ll sum(int x,int ls,int rs,int l,int r)
    {
        if(x==0) return 0;
        if(ls>=l&&rs<=r)
        {
            return T[x].s;
        }
        int z=ls+rs>>1;
        ll s=0;
        if(l<=z) s+=sum(T[x].l,ls,z,l,r);
        if(r>z) s+=sum(T[x].r,z+1,rs,l,r);
        return s;
    }
}
void dfs(int x,int fa)
{
    T[x].b=++tot;
    rt[tot]=rt[tot-1];
    T[x].d=T[fa].d+1;
    w+=f[T[x].d];
    for(int i=0;i<b[x].size();++i)
    {
        ++w;
        --f[T[x].d+b[x][i]+1];
    }
    Segment_tree::add(rt[tot],1,n,T[x].d,w);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
    }
    T[x].bm=tot;
    for(int i=0;i<b[x].size();++i)
    {
        --w;
        ++f[T[x].d+b[x][i]+1];
    }
    w-=f[T[x].d];
}
int main()
{
    read(n),read(m),read(q);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        read(x),read(y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        read(x),read(y);
        b[x].push_back(y);
    }
    dfs(1,0);
    for(int i=1;i<=q;++i)
    {
        int x,y;
        read(x),read(y);
        print(Segment_tree::sum(rt[T[x].bm],1,n,T[x].d,T[x].d+y)-Segment_tree::sum(rt[T[x].b-1],1,n,T[x].d,T[x].d+y));
        putchar('\n');
    }
    return 0;
}