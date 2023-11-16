#pragma GCC optimize("Ofast")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
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
int n,q,s,a[N],b[N],d[N];
namespace Segment_tree
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
        if(l==r) return;
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
}
struct str
{
    int l,r;
    str(){}
    str(int l,int r):l(l),r(r){}
    friend bool operator <(str a,str b)
    {
        return a.l<b.l;
    }
};
vector<int> c[N];
set<str> Set;
set<int> Set2;
void print()
{
    set<str>::iterator p=Set.begin();
    while(p!=Set.end())
    {
        printf("%d,%d|",(*p).l,(*p).r);
        ++p;
    }
    printf("\n");
}
void solve(int l,int r,int k)
{
    Set.insert(str(l,r));
    Segment_tree::add(1,l,(r-l)/2);
    int x=l,y=r;
    if(a[l]>=k&&a[r]>=k) x=l,y=r;
    else if(a[l]>=k&&a[r]<k) x=l,y=(l+r)/2;
    else if(a[l]<k&&a[r]>=k) x=(l+r)/2+1,y=r;
    else return;
    set<int>::iterator p=Set2.lower_bound(x),p2;
    while(p!=Set2.end()&&(*p)<=y)
    {
        d[*p]=k;
        p2=p;
        ++p;
        Set2.erase(p2);
    }
}
void add(int x,int k)
{
    set<str>::iterator p=--Set.upper_bound(str(x,x)),p1=p,p2=p;
    --p1,++p2;
    str z=(*p),z1=(*p1),z2=(*p2);
    int l=x,r=x;
    if(z.l==x&&z1.l!=0) l=z1.l,Set.erase(p1),Segment_tree::add(1,z1.l,0);
    if(z.r==x&&z2.r!=n+1) r=z2.r,Set.erase(p2),Segment_tree::add(1,z2.r,0);
    Segment_tree::add(1,z.l,0);
    Set.erase(p);
    if(z.l<x) solve(z.l,x-1,k);
    if(z.r>x) solve(x+1,z.r,k);
    solve(l,r,k);
}
int main()
{
    read(n);
    for(int i=1;i<=n;++i)
    {
        read(a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    q=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+q+1,a[i])-b;
        c[a[i]].push_back(i);
    }
    Set.insert(str(0,0));
    Set.insert(str(n+1,n+1));
    for(int i=1;i<=n;++i) Set.insert(str(i,i));
    for(int i=1;i<=n;++i) Set2.insert(i);
    Segment_tree::build(1,1,n);
    for(int i=q;i>=1;--i)
    {
        for(int j=0;j<c[i].size();++j) add(c[i][j],i);
        s=max(s,Segment_tree::T[1].s);
    }
    print(s);
    putchar('\n');
    for(int i=1;i<=n;++i)
    {
        print(b[d[i]]);
        putchar(' ');
    }
    return 0;
}