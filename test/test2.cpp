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
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=7e5+50;

namespace IO {
#define iL (1 << 20)
char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
#define gc() ((iS == iT) ? (iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin), iS == iT ? EOF : *iS ++) : *iS ++)
template<class T> inline void read(T &x) {
  x = 0;int f = 0;char ch = gc();
  for (; !isdigit(ch); f |= ch == '-', ch = gc());
  for (; isdigit(ch); x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc());
  x = (f == 1 ? ~ x + 1 : x);
}
template<class T, class... Args> inline void read(T &x, Args&... args) { read(x), read(args...); }
template<class T> inline void readch(T &x) { char ch = gc(); for (; ch!='A'&&ch!='C'&&ch!='?'; ch = gc()); x = ch; }
char Out[iL], *iter = Out;
#define flush() fwrite(Out, 1, iter - Out, stdout), iter = Out
template<class T> inline void write(T x, char ch = '\n') {
  T l, c[35];
  if (x < 0) *iter ++ = '-', x = ~ x + 1;
  for (l = 0; !l || x; c[l] = x % 10, l++, x /= 10);
  for (; l; -- l, *iter ++ = c[l] + '0');*iter ++ = ch;
  flush();
}
template<class T, class... Args> inline void write(T x, Args... args) { write(x, ' '), write(args...); }
} // IO
using namespace IO;

int n,q,f[N],g[N],B,fa[N],ff[N],top[N],siz[N],son[N],dep[N],p[N],t[N],dfn[N],now[N],in[N];
vector<int>to[N],vt,tson[N];
char s[N],c[N];

int LCA(int u,int v)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]])swap(u,v);
        u=fa[top[u]];
    }
    return dep[u]<dep[v]?u:v;
}

int st[N];

void ADD(int x,int y)
{
    to[x].push_back(y);ff[y]=x;in[x]=in[y]=1;
}

void add(int&top)
{
	ADD(st[top-1],st[top]);
	top--;
}

void rebuild(int k)
{
	int top=0;st[++top]=1;in[1]=t[0]=1;
	for(int i=1;i<=k;i++)if(t[i]!=t[i-1])
	{
		int lca=LCA(t[i],st[top]);
		while(dep[lca]<=dep[st[top-1]])add(top);
		if(lca!=st[top])ADD(lca,st[top]),st[top]=lca;
		if(t[i]!=lca)st[++top]=t[i];
	}
	while(top>1)add(top);
}

int cmp(int a,int b)
{
    return dfn[a]<dfn[b];
}

struct node
{
    int x,num;ll sum;
};

int tim,tt,dd;

struct block
{
    vector<int>p;
    node *a;
    int num,n;ll sum;// F
    int pos,ad;//G

    void clear()
    {
        vector<int>().swap(p);free(a);
        num=n=sum=pos=ad=0;
    }

    void init()
    {
        sort(p.begin(),p.end());
        a=new node[p.size()+4];
        a[0]=(node){-1000000000,0,0};
        for(auto x:p)
        {
            if(x!=a[n].x)a[++n]=(node){x,1,x};
            else a[n].num++,a[n].sum+=x;
        }
        a[++n]=(node){1000000000,0,0};
        for(int i=n-1;i>=0;i--)a[i].sum+=a[i+1].sum,a[i].num+=a[i+1].num;
        for(int i=1;i<=n;i++)if(a[i].x>0)
        {
            pos=i;
            break;
        }
    }

    void fad(int x)
    {
        sum+=x*num;
    }

    void gad(int x)
    {
        ad-=x;
        if(x>0&&a[pos-1].x>ad)pos--;
        if(x<0&&a[pos].x<=ad)pos++;
    }

    ll sol()
    {
        return sum+a[pos].sum-ad*a[pos].num;
    }

    void insert(char c,int x)
    {
        if(c=='?'&&g[x]+dd>0)p.push_back(g[x]);
        if(c=='A')sum+=f[x],num++;
    }
}d1[N],d2[N];

void clear(int x)
{
    in[x]=ff[x]=0;
    d1[x].clear();
    d2[x].clear();
    for(auto v:to[x])clear(v);
    vector<int>().swap(to[x]);
}

void GAD(int x,int w)
{
    d1[x].gad(w);d2[x].gad(w);g[x]+=w;
    for(auto v:to[x])GAD(v,w);
}

void rmk(int x,char s,char c)
{
    if(s==c)return;
    int rx=x;
    if(s=='A'||c=='A')
    {
        int w=(s=='A')?1:-1;
        d1[x].fad(w),d1[x].gad(w),x=ff[x];
        while(x)d1[x].fad(w),d1[x].gad(w),f[x]+=w,g[x]+=w,x=ff[x];
    }
    if(s=='C'||c=='C')
    {
        int w=(s=='C')?1:-1;
        d2[x=rx].gad(-w);
        for(auto v:to[x])GAD(v,-w);
    }
}

void sol()
{
    ll ans=0;
    for(auto x:vt)ans+=(s[x]=='A')*f[x]+(s[x]=='?')*max(0,g[x])+d1[x].sol()+d2[x].sol();
    write(ans);
}

char rs[N];

void chk(int x,char c)
{
    char s=rs[x];
    if(s==c)return;
    int ff=0;
    if(s=='A'||c=='A')ff|=(s=='A');
    if(s=='C'||c=='C')ff|=(c=='C');
    dd+=ff;rs[x]=c;
}

int up[N],dn[N];

void solve(int q)
{
    int bg=clock();
    vector<int>().swap(vt);
    for(int i=1;i<=n;i++)f[i]=g[i]=up[i]=dn[i]=0;
    for(int i=n;i>=1;i--)f[fa[i]]+=f[i]+(s[i]!='A');
    for(int i=2;i<=n;i++)g[i]=g[fa[i]]-(s[fa[i]]!='C');
    for(int i=1;i<=n;i++)g[i]+=f[i];
    for(int i=1;i<=q;i++)read(p[i]),readch(c[i]),t[i]=p[i],rs[p[i]]=s[i];
    dd=0;
    for(int i=1;i<=q;i++)chk(p[i],c[i]);
    sort(t+1,t+1+q,cmp);rebuild(q);
    for(int i=1;i<=n;i++)up[i]=in[i]?i:up[fa[i]];
    for(int i=n;i>=1;i--)dn[i]=in[i]?i:dn[i],dn[fa[i]]+=dn[i];
    for(int i=1;i<=n;i++)if(s[i]!='C'&&!in[i])
    {
        if(dn[i])d1[dn[i]].insert(s[i],i);
        else d2[up[i]].insert(s[i],i);
    }
    tim+=clock()-bg;bg=clock();
    for(int i=1;i<=n;i++)if(in[i])vt.push_back(i),d1[i].init(),d2[i].init();
    for(int i=1;i<=q;i++)rmk(p[i],s[p[i]],c[i]),s[p[i]]=c[i],sol();
    tt+=clock()-bg;
    clear(1);
}

int cc;
void dfs2(int x,int topp)
{
    top[x]=topp;dfn[x]=++cc;
    if(!son[x])return;dfs2(son[x],topp);
    for(auto v:tson[x])if(v!=son[x])dfs2(v,v);
}

char ss[5]={'A','?','C'};

main()
{
    read(n,q);
    for(int i=1;i<=n;i++)readch(s[i]);
    B=1000;dep[1]=1;
    for(int i=2;i<=n;i++)read(fa[i]),dep[i]=dep[fa[i]]+1,tson[fa[i]].push_back(i);
    for(int i=n;i>=1;i--)siz[i]++,siz[fa[i]]+=siz[i];
    siz[0]=0;
    for(int i=2;i<=n;i++)if(siz[i]>siz[son[fa[i]]])son[fa[i]]=i;
    dfs2(1,1);
    while(q>0)solve(min(q,B)),q-=B;
    // cout<<1.0*tim/CLOCKS_PER_SEC<<' '<<1.0*tt/CLOCKS_PER_SEC;
}