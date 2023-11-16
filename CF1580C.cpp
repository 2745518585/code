#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
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
const int N=300001,M=1001;
int n,m,q,p,s,a[N],b[N],c[N],e[N],f[N],g[M][M];
vector<int> d[N];
int main()
{
    read(n),read(m);
    q=800;
    for(int i=1;i<=n;++i)
    {
        read(a[i]),read(b[i]);
        if(a[i]+b[i]<=q) e[++p]=a[i]+b[i];
    }
    sort(e+1,e+p+1);
    p=unique(e+1,e+p+1)-e-1;
    for(int i=1;i<=m;++i)
    {
        int z,x;
        read(z),read(x);
        if(z==1)
        {
            if(a[x]+b[x]<=q)
            {
                c[x]=i;
                for(int j=c[x]+a[x];j<=c[x]+a[x]+b[x]-1;++j) ++g[a[x]+b[x]][j%(a[x]+b[x])];
            }
            else
            {
                c[x]=i;
                f[x]=0;
                if(i+a[x]<=m) d[i+a[x]].push_back(x);
            }
        }
        else if(z==2)
        {
            if(a[x]+b[x]<=q)
            {
                for(int j=c[x]+a[x];j<=c[x]+a[x]+b[x]-1;++j) --g[a[x]+b[x]][j%(a[x]+b[x])];
                c[x]=0;
            }
            else
            {
                c[x]=0;
                s-=f[x];
                f[x]=0;
            }
        }
        for(auto j:d[i])
        {
            if(c[j]==0) continue;
            s-=f[j];
            if((i-c[j])%(a[j]+b[j])<a[j])
            {
                f[j]=0;
                if(i+a[j]<=m) d[i+a[j]].push_back(j);
            }
            else
            {
                f[j]=1;
                if(i+b[j]<=m) d[i+b[j]].push_back(j);
            }
            s+=f[j];
        }
        int w=s;
        for(int j=1;j<=p;++j) w+=g[e[j]][i%e[j]];
        print(w);
        putchar('\n');
    }
    return 0;
}