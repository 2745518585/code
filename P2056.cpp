#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=200001,M=31;
int n,m,q,u,t[N],b[N],p=1,r,tot,rt,rt1[N],rt2[N],z1[N],z2[N];
bool g[N];
struct num
{
    int s,s2;
    num(){}
    num(int s,int s2):s(s),s2(s2){}
};
struct tree
{
    int s,ms,k,f[M],d[M];
}T[N];
struct tree2
{
    int l,r,s;
    num s2;
}T2[N<<6];
struct road
{
    int m,q;
}a[N<<1];
num update(num a,num b)
{
    if(a.s<b.s) swap(a,b);
    return (num){a.s,max(a.s2,b.s)};
}
void pushup(int x)
{
    T2[x].s=T2[T2[x].l].s+T2[T2[x].r].s;
    T2[x].s2=update(T2[T2[x].l].s2,T2[T2[x].r].s2);
}
void add(int &x,int ls,int rs,int q,int k)
{
    if(q<0) return;
    if(x==0) x=++tot;
    if(ls==rs)
    {
        T2[x].s+=k;
        if(T2[x].s==0) T2[x].s2=num(-1e9,-1e9);
        else if(T2[x].s==1) T2[x].s2=num(ls-1,-1e9);
        else T2[x].s2=num(ls-1,ls-1);
        return;
    }
    int z=ls+rs>>1;
    if(q<=z) add(T2[x].l,ls,z,q,k);
    else add(T2[x].r,z+1,rs,q,k);
    pushup(x);
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs1(int x,int fa)
{
    ++T[x].k;
    T[x].s=1;
    T[x].ms=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        dfs1(a[i].m,x);
        T[x].s+=T[a[i].m].s;
        T[x].ms=max(T[x].ms,T[a[i].m].s);
    }
    T[x].ms=max(T[x].ms,q-T[x].s);
    if(T[x].ms<T[r].ms) r=x;
}
void dfs2(int x,int fa)
{
    if(T[x].k>1) add(rt2[r],1,n,T[x].d[T[x].k-1]+1,1);
    T[x].f[T[x].k]=r;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa||g[a[i].m]) continue;
        T[a[i].m].d[T[x].k]=T[x].d[T[x].k]+1;
        dfs2(a[i].m,x);
    }
}
void dfs(int x)
{
    r=0;
    q=T[x].s;
    dfs1(x,0);
    T[r].d[T[r].k]=0;
    dfs2(r,0);
    g[r]=true;
    for(int i=t[r];i!=0;i=a[i].q)
    {
        if(g[a[i].m]) continue;
        dfs(a[i].m);
    }
}
void check(int x)
{
    if(b[x]==0)
    {
        for(int i=1;i<=T[x].k;++i)
        {
            z1[i]=T2[rt1[T[x].f[i]]].s2.s+T2[rt1[T[x].f[i]]].s2.s2;
            if(i<T[x].k) z2[i]=T2[rt2[T[x].f[i+1]]].s2.s;
            else add(rt1[T[x].f[i]],1,n,1,-1);
            if(i>1) add(rt2[T[x].f[i]],1,n,T[x].d[i-1]+1,-1);
        }
        for(int i=1;i<=T[x].k;++i)
        {
            if(i<T[x].k&&T2[rt2[T[x].f[i+1]]].s2.s!=z2[i])
            {
                add(rt1[T[x].f[i]],1,n,z2[i]+1,-1);
                add(rt1[T[x].f[i]],1,n,T2[rt2[T[x].f[i+1]]].s2.s+1,1);
            }
            if(T2[rt1[T[x].f[i]]].s2.s+T2[rt1[T[x].f[i]]].s2.s2!=z1[i])
            {
                add(rt,1,n,z1[i]+1,-1);
                add(rt,1,n,T2[rt1[T[x].f[i]]].s2.s+T2[rt1[T[x].f[i]]].s2.s2+1,1);
            }
        }
        b[x]=1;
        --u;
    }
    else if(b[x]==1)
    {
        for(int i=T[x].k;i>=1;--i)
        {
            z1[i]=T2[rt1[T[x].f[i]]].s2.s+T2[rt1[T[x].f[i]]].s2.s2;
            if(i<T[x].k) z2[i]=T2[rt2[T[x].f[i+1]]].s2.s;
        }
        for(int i=T[x].k;i>=1;--i)
        {
            if(i>1) add(rt2[T[x].f[i]],1,n,T[x].d[i-1]+1,1);
            if(i<T[x].k) 
            {
                if(T2[rt2[T[x].f[i+1]]].s2.s!=z2[i])
                {
                    add(rt1[T[x].f[i]],1,n,z2[i]+1,-1);
                    add(rt1[T[x].f[i]],1,n,T2[rt2[T[x].f[i+1]]].s2.s+1,1);
                }
            }
            else add(rt1[T[x].f[i]],1,n,1,1);
            if(T2[rt1[T[x].f[i]]].s2.s+T2[rt1[T[x].f[i]]].s2.s2!=z1[i])
            {
                add(rt,1,n,z1[i]+1,-1);
                add(rt,1,n,T2[rt1[T[x].f[i]]].s2.s+T2[rt1[T[x].f[i]]].s2.s2+1,1);
            }
        }
        b[x]=0;
        ++u;
    }
}
int main()
{
    T2[0].s2=num(-1e9,-1e9);
    u=n=read();
    for(int i=1;i<=n-1;++i)
    {
        int x=read(),y=read();
        road(x,y);
        road(y,x);
    }
    T[1].s=n;
    T[0].ms=1e9;
    dfs(1);
    for(int i=1;i<=n;++i)
    {
        add(rt1[i],1,n,1,1);
        if(T[i].k>1) add(rt1[T[i].f[T[i].k-1]],1,n,T2[rt2[i]].s2.s+1,1);
    }
    for(int i=1;i<=n;++i) add(rt,1,n,T2[rt1[i]].s2.s+T2[rt1[i]].s2.s2+1,1);
    m=read();
    int las=-1e9;
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='G')
        {
            if(las!=-1e9) printf("%d\n",las);
            else if(u==0) printf("%d\n",las=-1);
            else printf("%d\n",las=max(T2[rt].s2.s,0));
        }
        else if(z[0]=='C')
        {
            check(read());
            las=-1e9;
        }
    }
    return 0;
}