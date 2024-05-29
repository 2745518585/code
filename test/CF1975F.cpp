#pragma GCC optimize("Ofast","inline")
#include<cstdio>
#include<algorithm>
#include<vector>
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
const int N=21;
int n,a[1<<N],b[1<<N],d[N],f[1<<N],h[1<<N];
int main()
{
    read(n);
    for(int i=1;i<=(1<<n)-1;++i) read(a[i]);
    for(int i=1;i<=(1<<n)-1;++i)
    {
        b[i]=b[i^(i&-i)]+1;
    }
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=n;++j) d[j]=0;
        d[i]=1;
        for(int j=i+1;j<=n;++j)
        {
            int w=1;
            for(int k=j-1;k>=i;--k)
            {
                w*=(k+1);
                w/=(j-k);
                d[j]-=d[k]*w;
            }
        }
        for(int j=0;j<=(1<<n)-1;++j)
        {
            if(a[j]&(1<<i)) f[j]=1;
            else f[j]=0;
        }
        for(int j=0;j<=n-1;++j)
        {
            for(int k=0;k<=(1<<n)-1;++k)
            {
                if(k&(1<<j)) f[k^(1<<j)]+=f[k];
            }
        }
        for(int j=0;j<=(1<<n)-1;++j)
        {
            f[j]*=d[b[j]];
        }
        for(int j=0;j<=n-1;++j)
        {
            for(int k=0;k<=(1<<n)-1;++k)
            {
                if(k&(1<<j)) f[k]+=f[k^(1<<j)];
            }
        }
        for(int j=0;j<=(1<<n)-1;++j) h[j]+=f[j];
    }
    int s=0;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        if(h[i]==(1<<n)-1) ++s;
    }
    print(s),putchar('\n');
    for(int i=0;i<=(1<<n)-1;++i)
    {
        if(h[i]==(1<<n)-1) print(i),putchar('\n');
    }
    return 0;
}