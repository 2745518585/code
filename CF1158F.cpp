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
typedef long long ll;
const int N=5001;
constexpr int P=998244353;
int n,m,a[N],d[N],f[N][N],g[N][N],h[N],pow2[N],iv[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    x=(x%P+P)%P;
    return x;
}
void solve()
{
    f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=n/m;++j)
        {
            for(int k=(1<<m)-1;k>=0;--k)
            {
                f[j][k|(1<<(a[i]-1))]=(f[j][k|(1<<(a[i]-1))]+f[j][k])%P;
            }
        }
        for(int j=0;j<=n/m;++j)
        {
            f[j+1][0]=(f[j+1][0]+f[j][(1<<m)-1])%P;
            f[j][(1<<m)-1]=0;
        }
    }
    for(int i=0;i<=n;++i)
    {
        int s=0;
        for(int j=0;j<=(1<<m)-1;++j) s=(s+f[i][j])%P;
        print(s-(i==0));
        putchar(' ');
    }
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=n;++i) read(a[i]);
    if(m<=10)
    {
        solve();
        return 0;
    }
    pow2[0]=1;
    for(int i=1;i<=n;++i) pow2[i]=(ll)pow2[i-1]*2%P;
    for(int i=0;i<=n;++i) iv[i]=inv(pow2[i]-1)%P;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j) h[j]=0;
        int z=0,j=i;
        for(;j<=n;++j)
        {
            if(h[a[j]]==0) ++z;
            ++h[a[j]];
            if(z==m) break;
            g[i][j]=0;
        }
        int w=1;
        for(int j=1;j<=m;++j) w=(ll)w*(pow2[h[j]]-1)%P;
        for(;j<=n;++j)
        {
            g[i][j]=(ll)w*iv[h[a[j]]]%P;
            ++h[a[j+1]];
            w=(ll)w*iv[h[a[j+1]]-1]%P*(pow2[h[a[j+1]]]-1)%P;
        }
    }
    f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=i-m;++j)
        {
            if(g[j+1][i]==0) continue;
            const int x=g[j+1][i];
            for(int k=1;k<=n/m;++k)
            {
                f[i][k]=(f[i][k]+(ll)x*f[j][k-1])%P;
            }
        }
    }
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=n/m;++j)
        {
            d[j]=(d[j]+(ll)f[i][j]*pow2[n-i]%P)%P;
        }
    }
    --d[0];
    for(int i=0;i<=n;++i)
    {
        print(((d[i]-d[i+1])%P+P)%P);
        putchar(' ');
    }
    return 0;
}