#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
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
const int N=3000001;
int n,sa[N],rk[N],he[N],f[N],g[N];
char a[N],b[N];
namespace SA
{
    int h[N],x1[N],x2[N];
    void init(char a[])
    {
        int n=strlen(a+1),m=128;
        for(int i=1;i<=n;++i)
        {
            ++h[a[i]];
            x1[i]=a[i];
        }
        for(int i=1;i<=m;++i) h[i]+=h[i-1];
        for(int i=n;i>=1;--i) sa[h[x1[i]]--]=i;
        for(int r=1;r<=n;r<<=1)
        {
            int p=0;
            for(int i=n-r+1;i<=n;++i) x2[++p]=i;
            for(int i=1;i<=n;++i) if(sa[i]>r) x2[++p]=sa[i]-r;
            for(int i=1;i<=m;++i) h[i]=0;
            for(int i=1;i<=n;++i) ++h[x1[i]];
            for(int i=1;i<=m;++i) h[i]+=h[i-1];
            for(int i=n;i>=1;--i) sa[h[x1[x2[i]]]--]=x2[i],x2[i]=0;
            swap(x1,x2);
            p=0;
            x1[sa[1]]=++p;
            for(int i=2;i<=n;++i)
            {
                if(x2[sa[i]]==x2[sa[i-1]]&&x2[sa[i]+r]==x2[sa[i-1]+r]) x1[sa[i]]=p;
                else x1[sa[i]]=++p;
            }
            if(p==n) break;
            m=p;
        }
        for(int i=1;i<=n;++i) rk[sa[i]]=i;
        int p=0;
        for(int i=1;i<=n;++i)
        {
            if(rk[i]==1) continue;
            if(p>=1) --p;
            int j=sa[rk[i]-1];
            while(i+p<=n&&j+p<=n&&a[i+p]==a[j+p]) ++p;
            he[rk[i]]=p;
        }
    }
}
namespace ST
{
    int b[31][N],lg[N];
    void init()
    {
        for(int i=1;i<=n;++i) b[0][i]=he[i];
        for(int i=1;i<=21;++i)
        {
            for(int j=(1<<i);j<=min((1<<(i+1))-1,n);++j) lg[j]=i;
        }
        for(int i=1;i<=21;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j+(1<<i)-1<=n) b[i][j]=min(b[i-1][j],b[i-1][j+(1<<(i-1))]);
            }
        }
    }
    int sum(int x,int y)
    {
        x=rk[x],y=rk[y];
        if(x>y) swap(x,y);
        ++x;
        return min(b[lg[y-x]][x],b[lg[y-x]][y-(1<<lg[y-x])+1]);
    }
}
bool check(int x,int y,int t)
{
    if(x>y) swap(x,y);
    if(y<=t)
    {
        if(ST::sum(x,y)<t-y) return false;
        if(a[t-y+x]!=b[t]) return false;
        if(t-x+y<=n)
        {
            if(ST::sum(t-y+x+1,t+1)<y-x-1) return false;
            if(b[t]!=a[t-x+y]) return false;
            if(ST::sum(t+1,t-x+y+1)<n-t+x-y) return false;
        }
        else
        {
            if(ST::sum(t-y+x+1,t+1)<n-t) return false;
        }
    }
    else if(x<=t)
    {
        if(t-x+y<=n)
        {
            if(ST::sum(x,y)<t-x) return false;
            if(b[t]!=a[t-x+y]) return false;
            if(ST::sum(t+1,t-x+y+1)<n-t+x-y) return false;
        }
        else
        {
            if(ST::sum(x,y)<n-y+1) return false;
        }
    }
    else
    {
        if(ST::sum(x,y)<n-y+1) return false;
    }
    return true;
}
int main()
{
    scanf("%s%s",a+1,b+1);
    n=strlen(a+1);
    SA::init(a);
    ST::init();
    for(int i=1;i<=n-1;++i)
    {
        int p=ST::sum(1,n-i+1)+1;
        if(p==i+1)
        {
            g[i]=max(g[i],i);
            continue;
        }
        if(check(1,n-i+1,p)) f[p]=max(f[p],i);
        if(check(1,n-i+1,n-i+p)) f[n-i+p]=max(f[n-i+p],i);
    }
    for(int i=1;i<=n;++i) g[i]=max(g[i],g[i-1]);
    for(int i=1;i<=n;++i)
    {
        if(a[i]==b[i]) print(g[n]),putchar('\n');
        else print(max(f[i],g[min(i-1,n-i)])),putchar('\n');
    }
    return 0;
}