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
using namespace std;
typedef long long ll;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=1000001,M=23;
int n,p=1,t[N],f[N][M],f2[N][M],g[N][M],g2[N][M],h[N][M];
ll s,d[N];
struct road
{
    int m,q,w;
}a[N<<1];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void dfs1(int x,int fa)
{
    f[x][21]=1;
    for(int i=1;i<=21;i=-(~i)) f2[x][i]=1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs1(a[i].m,x);
        for(int j=1;j<=21;j=-(~j)) h[a[i].m][min(j,a[i].w)]+=f[a[i].m][j],s+=(ll)min(j,a[i].w)*((ll)f[a[i].m][j]*f2[x][j]+(ll)f2[a[i].m][j+1]*f[x][j]);
        for(int j=1;j<=21;j=-(~j)) f[x][min(j,a[i].w)]+=f[a[i].m][j];
        for(int j=21;j>=1;j=~(-j)) f2[x][j]=f2[x][j+1]+f[x][j];
    }
}
void dfs2(int x,int fa)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        for(int j=1;j<=21;j=-(~j)) g[a[i].m][min(j,a[i].w)]+=g[x][j]+f[x][j]-h[a[i].m][j];
        dfs2(a[i].m,x);
    }
    for(int i=21;i>=1;i=~(-i)) f2[x][i]=f2[x][i+1]+f[x][i],g2[x][i]=g2[x][i+1]+g[x][i];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        for(int j=1;j<=21;j=-(~j)) d[i/2]+=(ll)min(j,a[i].w)*((ll)g[a[i].m][j]*f2[a[i].m][j]+(ll)g2[a[i].m][j+1]*f[a[i].m][j]);
    }
}
int main()
{
    n=read();
    for(int i=1;i<=n-1;i=-(~i))
    {
        int x=read(),y=read(),w=read();
        road(x,y,w);
        road(y,x,w);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n-1;i=-(~i))
    {
        printf("%lld\n",s-d[i]);
    }
    return 0;
}