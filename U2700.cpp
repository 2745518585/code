#include<bits/stdc++.h>
#define min(x,y) (x)<(y)?(x):(y)
#define max(x,y) (x)>(y)?(x):(y)
using namespace std;
typedef long long ll;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T> inline
void read(T& x)
{
    T f=1,b=0;char ch=gc();
    while (ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=gc();}
    while(ch>='0'&&ch<='9') b*=10,b+=ch-'0',ch=gc();
    x=f*b;return;
}
template<typename T> inline
void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int st[129]={0},k=0;
    while(x) st[++k]=x%10,x/=10;
    for(int i=k;i;i--) putchar(st[i]+'0');
}
const int N=2001;
const ll P=1e9+7;
int n,m,q,a1[N][N],a2[N][N];
ll f[N][N],g[N][N];
struct Segment_tree
{
    struct tree
    {
        int l,r,k;
    }T[N<<2];
    void pushdown(int x)
    {
        if(T[x].k==1e9) return;
        T[x<<1].k=min(T[x<<1].k,T[x].k);
        T[x<<1|1].k=min(T[x<<1|1].k,T[x].k);
        T[x].k=1e9;
    }
    void build(int x,int l,int r)
    {
        T[x].l=l;
        T[x].r=r;
        T[x].k=1e9;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
    }
    void add(int x,int l,int r,int k)
    {
        if(l>r) return;
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].k=min(T[x].k,k);
            return;
        }
        pushdown(x);
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
    }
    void sum1(int x,int t)
    {
        if(T[x].l==T[x].r)
        {
            a1[t][T[x].l]=T[x].k;
            return;
        }
        pushdown(x); 
        sum1(x<<1,t);
        sum1(x<<1|1,t);
    }
    void sum2(int x,int t)
    {
        if(T[x].l==T[x].r)
        {
            a2[T[x].l][t]=T[x].k;
            return;
        }
        pushdown(x); 
        sum2(x<<1,t);
        sum2(x<<1|1,t);
    }
}T1[N],T2[N];
struct Deque
{
    int Q[N],T,R,f[N<<1],g[N<<1],h[N<<1];
    void init()
    {
        T=1,R=0;
        for(int i=1;i<=4000;++i) h[i]=0;
    }
    void del(int x)
    {
        while(T<=R&&Q[T]<x) h[f[Q[T]]]=(h[f[Q[T]]]-g[Q[T]])%P,++T;
    }
    int sum()
    {
        if(T<=R) return f[Q[T]];
        return -1e9;
    }
    int sum2()
    {
        if(T<=R) return h[f[Q[T]]];
        return 0;
    }
    void add(int x,int a,int b)
    {
        f[x]=a,g[x]=b;
        while(T<=R&&f[Q[R]]<f[x]) h[f[Q[R]]]=(h[f[Q[R]]]-g[Q[R]])%P,--R;
        Q[++R]=x;
        h[f[x]]=(h[f[x]]+g[x])%P;
    }
}Q1[N],Q2[N];
void abc()
{
    read(m),read(n),read(q);
    for(int i=1;i<=m;++i)
    {
        T1[i].build(1,1,n);
    }
    for(int i=1;i<=n;++i)
    {
        T2[i].build(1,1,m);
    }
    for(int i=1;i<=q;++i)
    {
        int x1,y1,x2,y2;
        read(x1),read(y1),read(x2),read(y2);
        T1[x2].add(1,y1+1,y2,x1);
        T2[y2].add(1,x1+1,x2,y1);
    }
    for(int i=1;i<=m;++i)
    {
        T1[i].sum1(1,i);
    }
    for(int i=1;i<=n;++i)
    {
        T2[i].sum2(1,i);
    }
    for(int i=m;i>=1;--i)
    {
        for(int j=n;j>=1;--j)
        {
            if(i<m) a1[i][j]=min(a1[i][j],a1[i+1][j]);
            if(j<n) a2[i][j]=min(a2[i][j],a2[i][j+1]);
        }
    }
    for(int i=1;i<=m;++i) Q1[i].init();
    for(int i=1;i<=n;++i) Q2[i].init();
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            f[i][j]=1;
            g[i][j]=1;
            Q1[i].del(a2[i][j]);
            Q2[j].del(a1[i][j]);
            if(a1[i][j]<=i-1)
            {
                if(f[i-1][j-1]+1>f[i][j])
                {
                    f[i][j]=f[i-1][j-1]+1;
                    g[i][j]=g[i-1][j-1];
                }
                else if(f[i-1][j-1]+1==f[i][j])
                {
                    g[i][j]=(g[i][j]+g[i-1][j-1])%P;
                }
            }
            int x=Q1[i].sum(),y=Q1[i].sum2();
            if(x+1>f[i][j])
            {
                f[i][j]=x+1;
                g[i][j]=y;
            }
            else if(x+1==f[i][j])
            {
                g[i][j]=(g[i][j]+y)%P;
            }
            x=Q2[j].sum(),y=Q2[j].sum2();
            if(x+1>f[i][j])
            {
                f[i][j]=x+1;
                g[i][j]=y;
            }
            else if(x+1==f[i][j])
            {
                g[i][j]=(g[i][j]+y)%P;
            }
            if(i>=2&&j>=2) Q1[i].add(j-1,f[i-1][j-1],g[i-1][j-1]);
            if(i>=2&&j>=2) Q2[j].add(i-1,f[i-1][j-1],g[i-1][j-1]);
        }
    }
    ll s=0,q=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(f[i][j]>s)
            {
                s=f[i][j];
                q=g[i][j];
            }
            else if(f[i][j]==s) q=(q+g[i][j])%P;
        }
    }
    printf("%lld %lld\n",s,(q%P+P)%P);
}
int main()
{
    int T;
    read(T);
    while(T--) abc();
    return 0;
}