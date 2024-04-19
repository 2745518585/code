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
#include<stack>
#include<vector>
using namespace std;
typedef long long ll;
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
const int N=500001,M=1000;
int n,m,q,fa[N],fa2[N],f[N],g[N],f1[N],f2[N],g1[N],g2[N],d1[N],d2[N],*p1[N],*p2[N],pp[M<<3][(M<<1)+10],S[N],T;
ll v;
char b[N];
bool h[N],h1[N],h2[N];
vector<int> a[N],a2[N];
vector<pair<int,int>> cl;
struct
{
    int x,c;
}e[N];
inline void init()
{
    g[1]=0;
    for(int i=2;i<=n;++i)
    {
        g[i]=g[fa[i]];
        if(b[fa[i]]!='C') --g[i];
    }
    for(int i=n;i>=1;--i)
    {
        f[i]=0;
        int u=h[i];
        for(auto j:a[i])
        {
            u+=h1[j];
            f[i]+=f[j];
            if(b[j]!='A') ++f[i];
        }
        g[i]+=f[i];
        if(u>=2) h[i]=true;
        if(u>0) h1[i]=true;
    }
}
inline void add1(int x,int k)
{
    if(b[k]=='A') ++f1[x];
    if(b[k]=='?')
    {
        if(g[k]>0) ++g1[x];
        if(abs(g[k])<=M) ++p1[x][g[k]],cl.push_back(make_pair(x,g[k]));
    }
}
inline void add2(int x,int k)
{
    if(b[k]=='A') ++f2[x];
    if(b[k]=='?')
    {
        if(g[k]>0) ++g2[x];
        if(abs(g[k])<=M) ++p2[x][g[k]],cl.push_back(make_pair(x,g[k]));
    }
}
int dfs(int x)
{
    if(!h[x])
    {
        S[++T]=x;
        int u=0;
        for(auto i:a[x]) u+=dfs(i);
        return u;
    }
    S[++T]=x;
    p1[x]=pp[++q]+(M+5);
    p2[x]=pp[++q]+(M+5);
    if(x!=1)
    {
        int z=fa[x];
        while(!h[z])
        {
            add1(x,z);
            h2[z]=true;
            z=fa[z];
        }
    }
    for(auto i:a[x])
    {
        int z=dfs(i);
        if(z)
        {
            a2[x].push_back(z);
            fa2[z]=x;
        }
    }
    while(S[T]!=x)
    {
        if(h2[S[T]]==false) add2(x,S[T]);
        --T;
    }
    --T;
    return x;
}
void sum(int &g,int &d,int *p,int k)
{
    if(k==1)
    {
        g+=p[-d];
        ++d;
        v+=g;
    }
    else if(k==-1)
    {
        v-=g;
        --d;
        g-=p[-d];
    }
}
void solve1(int x,int k)
{
    while(x!=1)
    {
        v+=f1[x]*k;
        sum(g1[x],d1[x],p1[x],k);
        x=fa2[x];
        f[x]+=k,g[x]+=k;
    }
}
void solve2(int x,int k)
{
    sum(g2[x],d2[x],p2[x],k);
    for(auto i:a2[x])
    {
        sum(g1[i],d1[i],p1[i],k);
        g[i]+=k;
        solve2(i,k);
    }
}
void solve(int l,int r)
{
    // fprintf(stderr,"%d %d\n",l,r);
    // fflush(stderr);
    for(int i=1;i<=n;++i)
    {
        f1[i]=f2[i]=g1[i]=g2[i]=d1[i]=d2[i]=0;
        h[i]=h1[i]=h2[i]=false;
        a2[i].clear();
    }
    q=0;
    cl.clear();
    v=0;
    for(int i=l;i<=r;++i) h[e[i].x]=true;
    h[1]=true;
    init();
    dfs(1);
    // return;
    static int p[N],t=0;
    t=0;
    for(int i=1;i<=n;++i)
    {
        if(h[i]) p[++t]=i;
        else if(b[i]=='A') v+=f[i];
        else if(b[i]=='?') v+=max(g[i],0);
    }
    for(int i=l;i<=r;++i)
    {
        int x=e[i].x,c=e[i].c;
        if((b[x]!='A')^(c!='A'))
        {
            solve1(x,b[x]!='A'?-1:1);
        }
        if((b[x]!='C')^(c!='C'))
        {
            solve2(x,b[x]!='C'?1:-1);
        }
        b[x]=c;
        ll w=v;
        for(int j=1;j<=t;++j)
        {
            if(b[p[j]]=='A') w+=f[p[j]];
            else if(b[p[j]]=='?') w+=max(g[p[j]],0);
        }
        print(w);
        putchar('\n');
    }
    for(auto i:cl) p1[i.first][i.second]=p2[i.first][i.second]=0;
}
int main()
{
    read(n,m);
    for(int i=1;i<=n;++i)
    {
        b[i]=gc();
        while(b[i]!='A'&&b[i]!='C'&&b[i]!='?') b[i]=gc();
    }
    for(int i=2;i<=n;++i)
    {
        int x;
        read(x);
        a[x].push_back(i);
        fa[i]=x;
    }
    for(int i=1;i<=m;++i)
    {
        read(e[i].x);
        e[i].c=gc();
        while(e[i].c!='A'&&e[i].c!='C'&&e[i].c!='?') e[i].c=gc();
    }
    for(int i=1;i<=m;++i)
    {
        int j=min(i+M-1,m);
        solve(i,j);
        i=j;
    }
    return 0;
}