#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
typedef unsigned long long ull;
typedef __int128_t lll;
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
const int N=300001,M=71;
int n,m,a[N],c[N],d[M],jc2[N],K;
ull pw[N],jc[N],ivjc[N],e[N],f[M],g[M],h[N][M];
lll B;
struct qry
{
    int l,r,t;
}b[N];
void exgcd(lll a,lll b,lll &x,lll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ull inv(lll a)
{
    lll x,y;
    exgcd(a,B,x,y);
    return x;
}
namespace sgt
{
    int T[N];
    void add(int x,int k)
    {
        while(x>=1) T[x]+=k,x-=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x<=n) s+=T[x],x+=x&-x;
        return s;
    }
}
ull C(int a,int b)
{
    if(a<b) return 0;
    return jc[a]*ivjc[b]*ivjc[a-b]*pw[min(jc2[a]-jc2[b]-jc2[a-b],64)];
}
void add(int x)
{
    --d[min(c[x],64)];
    ++c[x];
    ++d[min(c[x],64)];
}
void del(int x)
{
    --d[min(c[x],64)];
    --c[x];
    ++d[min(c[x],64)];
}
bool cmp(qry a,qry b)
{
    if((a.l-1)/K!=(b.l-1)/K) return a.l<b.l;
    return a.r<b.r;
}
int main()
{
    B=1;
    for(int i=1;i<=64;++i) B*=2;
    pw[0]=1;
    for(int i=1;i<=64;++i) pw[i]=pw[i-1]*2;
    read(n,m);
    K=n/sqrt(m)+1;
    jc[0]=1,jc2[0]=0;
    for(int i=1;i<=n;++i)
    {
        ull x=i;
        while(x%2==0) ++jc2[i],x/=2;
        jc[i]=jc[i-1]*x,jc2[i]+=jc2[i-1];
    }
    ivjc[n]=inv(jc[n]);
    for(int i=n;i>=1;--i)
    {
        ull x=i;
        while(x%2==0) x/=2;
        ivjc[i-1]=ivjc[i]*x;
    }
    h[0][0]=1;
    for(int i=0;i<=n;++i)
    {
        h[i][0]=1;
        for(int j=1;j<=64;++j)
        {
            h[i][j]=h[i-1][j-1]+h[i-1][j];
        }
    }
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<=m;++i)
    {
        read(b[i].l,b[i].r);
        b[i].t=i;
    }
    sort(b+1,b+m+1,cmp);
    d[0]=n;
    int l=1,r=0;
    for(int i=1;i<=m;++i)
    {
        while(l>b[i].l) add(a[--l]);
        while(r<b[i].r) add(a[++r]);
        while(l<b[i].l) del(a[l++]);
        while(r>b[i].r) del(a[r--]);
        int t=0;
        for(int j=1;j<=64;++j) t+=d[j];
        for(int j=0;j<=64;++j) f[j]=g[j]=0;
        f[0]=1;
        for(int j=63;j>=0;--j)
        {
            for(int k=0;k<=64;++k) g[k]=f[k];
            ull w=1;
            for(int k=1;k<=d[j+1]&&(j+1)*k<=64;++k)
            {
                w*=pw[j];
                ull p=h[d[j+1]][k]*w;
                for(int l=k;(j+1)*l<=64;++l) f[l]+=g[l-k]*p;
            }
        }
        ull s=0;
        for(int j=t%2;j<=min(64,t);j+=2)
        {
            ull w=0;
            for(int k=j;k>=0;--k)
            {
                w+=((j-k)&1?-1:1)*f[k]*h[t-k][j-k];
            }
            s+=w*pw[j]*C(t-j,(t-j)/2);
        }
        e[b[i].t]=s;
    }
    for(int i=1;i<=m;++i)
    {
        print(e[i]);
        putchar('\n');
    }
    return 0;
}