#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
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
template<typename T>
inline void print(T x)
{
    if(x==0) return putchar('0'),void();
    if(x<0) putchar('-'),x=-x;
    int c[129]={0},k=0;
    while(x) c[++k]=x%10,x/=10;
    for(int i=k;i;--i) putchar(c[i]+'0');
}
const int N=500002,M=19;
int n,a[N],c[N],f[N],g[N];
ll d[N];
vector<int> e[N];
map<ll,int> Map[2];
multiset<int> Set;
struct str
{
    int w,s1,s2;
    str():w(0),s1(0),s2(1e9) {}
    str(int x):w(x),s1(1),s2(x-1) {}
    friend str operator+(const str &a,const str &b)
    {
        str c;
        if(a.s1>a.s2||b.s1>b.s2)
        {
            c.s1=1,c.s2=0;
            return c;
        }
        c.w=a.w+b.w;
        c.s1=max(a.s1,a.w+b.s1);
        c.s2=min(a.s2,a.w+b.s2);
        return c;
    }
    friend str operator-(const str &a,const str &b)
    {
        str c;
        if(a.s1>a.s2||b.s1>b.s2)
        {
            c.s1=1,c.s2=0;
            return c;
        }
        c.w=a.w-b.w;
        c.s1=max(a.s1,a.w-b.s2);
        c.s2=min(a.s2,a.w-b.s1);
        return c;
    }
}b[N][M];
int find1(int x)
{
    int t=0;
    str p;
    while(t>=0)
    {
        if(x-(1<<(t+1))+1>=1)
        {
            str z=p+b[x][t];
            if(z.s1<=z.s2)
            {
                p=p+b[x][t];
                x-=(1<<(t+1));
                ++t;
            }
            else --t;
        }
        else --t;
    }
    if(x>=1)
    {
        str z=p+a[x];
        if(z.s1<=z.s2) --x;
    }
    return x+1;
}
int find2(int x,int k)
{
    int t=0;
    str p;
    while(t>=0)
    {
        if(x-(1<<(t+1))+1>=1)
        {
            str z=p+b[x][t];
            if(z.s1<=k&&k<=z.s2)
            {
                p=p+b[x][t];
                x-=(1<<(t+1));
                ++t;
            }
            else --t;
        }
        else --t;
    }
    if(x>=1)
    {
        str z=p+a[x];
        if(z.s1<=k&&k<=z.s2) --x;
    }
    return x+1;
}
int find3(int x,int k)
{
    int t=0;
    str p;
    while(t>=0)
    {
        if(x+(1<<(t+1))-1<=n)
        {
            str z=p+b[x][t];
            if(z.s1<=k&&k<=z.s2)
            {
                p=p+b[x][t];
                x+=(1<<(t+1));
                ++t;
            }
            else --t;
        }
        else --t;
    }
    if(x<=n)
    {
        str z=p+a[x];
        if(z.s1<=k&&k<=z.s2) ++x;
    }
    return x-1;
}
namespace sgt
{
    int T[N<<2];
    void pushup(int x)
    {
        T[x]=max(T[x<<1],T[x<<1|1]);
    }
    void build(int x,int l,int r)
    {
        T[x]=-1e9;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int ls,int rs,int q,int k)
    {
        if(ls==rs)
        {
            T[x]=k;
            return;
        }
        int z=ls+rs>>1;
        if(q<=z) add(x<<1,ls,z,q,k);
        else add(x<<1|1,z+1,rs,q,k);
        pushup(x);
    }
    int sum(int x,int ls,int rs,int l,int r)
    {
        if(ls>=l&&rs<=r) return T[x];
        int z=ls+rs>>1,s=-1e9;
        if(l<=z) s=max(s,sum(x<<1,ls,z,l,r));
        if(r>z) s=max(s,sum(x<<1|1,z+1,rs,l,r));
        return s;
    }
}
int main()
{
    int T;
    read(T);
    while(T--)
    {
        read(n);
        for(int i=1;i<=n;++i)
        {
            read(a[i]);
            d[i]=a[i]-d[i-1];
        }
        for(int i=1;i<=n-1;++i) b[i][0]=str(a[i])-str(a[i+1]);
        for(int i=1;i<=19;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j+(1<<(i+1))-1<=n) b[j][i]=b[j][i-1]+b[j+(1<<i)][i-1];
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(a[i]%2==0) c[i]=find3(i,a[i]/2);
        }
        for(int i=2;i<=n;++i) b[i][0]=str(a[i])-str(a[i-1]);
        for(int i=1;i<=19;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(j-(1<<(i+1))+1>=1) b[j][i]=b[j][i-1]+b[j-(1<<i)][i-1];
            }
        }
        sgt::build(1,0,n);
        sgt::add(1,0,n,0,0);
        Map[0].clear(),Map[1].clear();
        Set.clear();
        for(int i=1;i<=n;++i) vector<int>().swap(e[i]);
        for(int i=1;i<=n;++i)
        {
            f[i]=g[i]=0;
            int x=find1(i);
            f[i]=max(f[i],sgt::sum(1,0,n,x-1,i-1)+i-1);
            if(a[i]%2==0)
            {
                int y=find2(i,a[i]/2);
                g[i]=max(g[i],sgt::sum(1,0,n,y-1,i-1)+i);
                int z=0;
                if(Map[i%2].count(d[i]-a[i]/2)) z=max(z,Map[i%2][d[i]-a[i]/2]);
                if(z>=y) g[i]=max(g[i],g[z]+(i-z)+1);
                Map[i%2][d[i]-a[i]/2]=i;
                Map[i%2^1][-d[i]+a[i]/2]=i;
                int p=c[i];
                Set.insert(-(g[i]-i));
                e[p+1].push_back(g[i]-i);
            }
            for(auto j:e[i]) Set.erase(Set.find(-j));
            vector<int>().swap(e[i]);
            if(!Set.empty()) f[i]=max(f[i],(-(*Set.begin()))+i);
            f[i]=max(f[i],g[i]);
            sgt::add(1,0,n,i,f[i]-i);
        }
        printf("%d\n",n*2-f[n]);
    }
    return 0;
}