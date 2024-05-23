#pragma GCC optimize("Ofast","inline")
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
const int N=250001,M=600;
const ll P=998244353;
int n,m,a[N],b[N],c[N],*f[N/M+1],*g[N/M+1],h[N];
namespace tc
{
    int lg[N];
    vector<int> a[N],fa1[N],fa2[N];
    struct tree
    {
        int f,l,d,t,z,fa[21];
    }T[N];
    void dfs1(int x)
    {
        T[x].l=1;
        T[x].d=T[T[x].f].d+1;
        T[x].fa[0]=T[x].f;
        for(int i=1;i<=20;++i)
        {
            T[x].fa[i]=T[T[x].fa[i-1]].fa[i-1];
        }
        for(auto i:a[x])
        {
            if(i==T[x].f) continue;
            T[i].f=x;
            dfs1(i);
            if(T[i].l+1>T[x].l)
            {
                T[x].l=T[i].l+1;
                T[x].z=i;
            }
        }
    }
    void dfs2(int x,int k)
    {
        fa2[k].push_back(x);
        T[x].t=k;
        for(auto i:a[x])
        {
            if(i==T[x].f) continue;
            if(i==T[x].z) dfs2(i,k);
            else
            {
                fa1[i].push_back(i);
                for(int j=1;j<=T[i].l;++j)
                {
                    fa1[i].push_back(T[fa1[i].back()].f);
                }
                dfs2(i,i);
            }
        }
    }
    int get(int x,int k)
    {
        if(k==0) return x;
        int q=T[x].d-k;
        x=T[T[x].fa[lg[k]]].t;
        if(T[x].d<q) return fa2[x][q-T[x].d];
        else return fa1[x][T[x].d-q];
        return x;
    }
    void init()
    {
        for(int i=2;i<=n;++i)
        {
            a[b[i]].push_back(i);
        }
        dfs1(1);
        fa1[1].push_back(1);
        for(int i=1;i<=T[1].l;++i)
        {
            fa1[1].push_back(T[fa1[1].back()].f);
        }
        dfs2(1,1);
        for(int i=0;i<=20;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
        }
    }
    int find(int x,int l,int r)
    {
        int z=get(x,T[x].d-(T[l].d+1));
        if(z<=c[l]) return z;
        else return b[z];
    }
}
int main()
{
    read(n,m);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=2;i<=n;++i) read(b[i]);
    tc::init();
    for(int i=1;i<=n;++i)
    {
        c[i]=c[i-1];
        while(c[i]<=n&&b[c[i]+1]<i) ++c[i];
    }
    for(int i=0;i<=n/M;++i)
    {
        f[i]=new int[(i+1)*M+10];
        g[i]=new int[(i+1)*M+10];
        f[i][0]=g[i][0]=0;
        for(int j=1;j<=min((i+1)*M,n);++j) f[i][j]=a[j];
        for(int j=i*M;j>=1;--j) f[i][b[j]]=(f[i][b[j]]+f[i][j])%P;
        for(int j=1;j<=min((i+1)*M,n);++j) g[i][j]=(g[i][j-1]+(ll)f[i][j]*f[i][j])%P;
    }
    int las=0;
    for(int i=1;i<=m;++i)
    {
        int l,r;
        read(l,r);
        l^=las,r^=las;
        int p=r/M;
        ll s=(g[p][min(r,c[l])]-g[p][l-1])%P;
        for(int j=max(p*M,c[l])+1;j<=r;++j)
        {
            int x=tc::find(j,l,r);
            s+=((ll)f[p][x]*2+a[j])*a[j]%P;
            f[p][x]=(f[p][x]+a[j])%P;
            h[j]=x;
        }
        for(int j=max(p*M,c[l])+1;j<=r;++j)
        {
            f[p][h[j]]=(f[p][h[j]]-a[j])%P;
        }
        print(las=((s%P+P)%P));
        putchar('\n');
    }
    return 0;
}