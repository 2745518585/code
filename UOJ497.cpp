#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
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
const int N=300001;
int n,tot,p,l[N<<6],fa[N],ga[N],Q[N<<6],T,R,b1[N],b2[N],c[N],d1[N<<6],d2[N<<6];
ll a[N],b[N<<6],f[N<<6],e1[N<<6],e2[N<<6];
struct str
{
    int m,q,w;
}c1[N<<8];
inline void add(int *t,int x,int y,int w)
{
    c1[++p].m=y;
    c1[p].q=t[x];
    t[x]=p;
    c1[p].w=w;
}
inline int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
inline int find1(int x,ll k)
{
    while(ga[x]<=n&&a[ga[x]]%k==0)
    {
        fa[ga[x]+1]=x;
        ga[x]=ga[ga[x]+1];
    }
    return ga[x];
}
inline int find2(int x,ll k)
{
    while(ga[x]>=1&&a[ga[x]]%k==0)
    {
        fa[ga[x]-1]=x;
        ga[x]=ga[ga[x]-1];
    }
    return ga[x];
}
int main()
{
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<=n;++i)
    {
        b[++tot]=a[i];
        add(c,i,i,tot);
    }
    for(int i=0;i<=n+1;++i) fa[i]=ga[i]=i;
    for(int i=n;i>=1;--i)
    {
        int x=ga[find(i)];
        ll w=a[i];
        while(x<=n)
        {
            w=__gcd(w,a[x]);
            b[++tot]=w;
            add(c,i,x,tot);
            x=find1(x+1,w);
        }
        b[++tot]=w;
        add(c,i,n,tot);
    }
    for(int i=0;i<=n+1;++i) fa[i]=ga[i]=i;
    for(int i=1;i<=n;++i)
    {
        int x=ga[find(i)];
        ll w=a[i];
        while(x>=1)
        {
            w=__gcd(w,a[x]);
            b[++tot]=w;
            add(c,x,i,tot);
            x=find2(x-1,w);
        }
        b[++tot]=w;
        add(c,1,i,tot);
    }
    fprintf(stderr,"%d\n",p);
    for(int i=1;i<=n;++i)
    {
        for(int j=c[i];j;j=c1[j].q)
        {
            if(c1[b1[c1[j].m]].m!=i) add(b1,c1[j].m,i,c1[j].w);
        }
    }
    fprintf(stderr,"%d\n",p);
    for(int i=n;i>=1;--i)
    {
        int z=0,p=i;
        for(int j=b1[i];j;j=c1[j].q)
        {
            if(z)
            {
                d1[z]=c1[j].w,e1[z]=b[z]*(p-c1[j].m-1)+b[c1[j].w];
                ++l[d1[z]];
            }
            z=c1[j].w,p=c1[j].m;
            add(b2,c1[j].m,i,c1[j].w);
        }
    }
    fprintf(stderr,"%d\n",p);
    for(int i=1;i<=n;++i)
    {
        int z=0,p=i;
        for(int j=b2[i];j;j=c1[j].q)
        {
            if(z)
            {
                d2[z]=c1[j].w,e2[z]=b[z]*(c1[j].m-p-1)+b[c1[j].w];
                ++l[d2[z]];
            }
            z=c1[j].w,p=c1[j].m;
        }
    }
    for(int i=1;i<=tot;++i) f[i]=1e18;
    for(int i=1;i<=n;++i)
    {
        Q[++R]=c1[b1[i]].w;
        f[c1[b1[i]].w]=0;
    }
    while(T<R)
    {
        const int k=Q[++T];
        const int z1=d1[k];
        if(z1)
        {
            f[z1]=min(f[z1],f[k]+e1[k]);
            if((--l[z1])==0) Q[++R]=z1;
        }
        const int z2=d2[k];
        if(z2)
        {
            f[z2]=min(f[z2],f[k]+e2[k]);
            if((--l[z2])==0) Q[++R]=z2;
        }
    }
    ll s=0,w=0;
    for(int i=b2[1];i;i=c1[i].q)
    {
        if(c1[i].m==n) s=f[c1[i].w];
    }
    for(int i=1;i<=n;++i) s+=a[i],w=__gcd(w,a[i]);
    s-=w;
    printf("%lld",s);
    return 0;
}