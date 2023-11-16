#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
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
const int N=2100001,M=31;
int n,m,a[N],d[N],g1[N],g2[N],g3[N],g4[N],g[M];
struct
{
    int l,r;
}b[N];
vector<pair<int,int>> c[N],b1[N],b3[N],b4[N];
vector<pair<pair<int,int>,int>> b2[N];
struct sgt1
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]=max(T[x],k),x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s=max(s,T[x]),x-=x&-x;
        return s;
    }
}T1;
struct sgt2
{
    struct tree
    {
        int l,r,s,k;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=max(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s=T[x].k=0;
        if(l==r) return;
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int l,int r,int k)
    {
        if(T[x].l>=l&&T[x].r<=r)
        {
            T[x].s=max(T[x].s,k);
            T[x].k=max(T[x].k,k);
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(l<=z) add(x<<1,l,r,k);
        if(r>z) add(x<<1|1,l,r,k);
        pushup(x);
    }
    int sum(int x,int q)
    {
        if(T[x].l==T[x].r) return T[x].s;
        int z=T[x].l+T[x].r>>1;
        if(q<=z) return max(sum(x<<1,q),T[x].k);
        else return max(sum(x<<1|1,q),T[x].k);
    }
}T2;
struct sgt3
{
    struct tree
    {
        int l,r,s,w;
    }T[N<<2];
    void pushup(int x)
    {
        T[x].s=min(T[x<<1].s,T[x<<1|1].s);
    }
    void build(int x,int l,int r)
    {
        T[x].l=l,T[x].r=r;
        T[x].s=1e9;
        if(l==r)
        {
            T[x].w=0;
            return;
        }
        int z=l+r>>1;
        build(x<<1,l,z);
        build(x<<1|1,z+1,r);
        pushup(x);
    }
    void add(int x,int q,int k) 
    {
        if(T[x].l==T[x].r)
        {
            T[x].w+=k;
            if(T[x].w==0) T[x].s=1e9;
            else T[x].s=T[x].l;
            return;
        }
        int z=T[x].l+T[x].r>>1;
        if(q<=z) add(x<<1,q,k);
        else add(x<<1|1,q,k);
        pushup(x);
    }
    int sum(int x,int l,int r)
    {
        if(T[x].l>=l&&T[x].r<=r) return T[x].s;
        int z=T[x].l+T[x].r>>1,s=1e9;
        if(l<=z) s=min(s,sum(x<<1,l,r));
        if(r>z) s=min(s,sum(x<<1|1,l,r));
        return s;
    }
}T3;
struct sgt4
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}T4;
void solve()
{
    for(int i=1;i<=n;++i)
    {
        vector<pair<int,int>>().swap(c[i]);
        vector<pair<int,int>>().swap(b1[i]);
        vector<pair<pair<int,int>,int>>().swap(b2[i]);
        vector<pair<int,int>>().swap(b3[i]);
        vector<pair<int,int>>().swap(b4[i]);
    }
    for(int i=1;i<=m;++i)
    {
        c[b[i].r].push_back(make_pair(b[i].l,i));
    }
    T2.build(1,1,n);
    T3.build(1,1,n);
    for(int i=1;i<=n;++i) T1.T[i]=T4.T[i]=0;
    for(int i=1;i<=n;++i)
    {
        int x0=g1[i],x1=g2[i],x2=g4[i];
        if(x0>=x1)
        {
            b1[x2].push_back(make_pair(x1,x2-x1+1));
            b2[x2].push_back(make_pair(make_pair(x1,x0),x2));
            T3.add(1,x1,1);
            b3[x2+1].push_back(make_pair(x1,-1));
            T4.add(x1,1),T4.add(x0+1,-1);
            b4[x2+1].push_back(make_pair(x1,x0));
        }
        for(auto j:b1[i]) T1.add(n-j.first+1,j.second);
        for(auto j:b2[i]) T2.add(1,j.first.first,j.first.second,j.second);
        for(auto j:b3[i]) T3.add(1,j.first,j.second);
        for(auto j:b4[i]) T4.add(j.first,-1),T4.add(j.second+1,1);
        for(auto j:c[i])
        {
            if(T4.sum(j.first)) d[j.second]=max(d[j.second],i-j.first+1);
            else
            {
                d[j.second]=max(d[j.second],T1.sum(n-j.first+1));
                d[j.second]=max(d[j.second],T2.sum(1,j.first)-j.first+1);
                d[j.second]=max(d[j.second],i-T3.sum(1,j.first,i)+1);
            }
        }
    }
}
int main()
{
    int TOT;
    read(TOT);
    int z;
    read(z);
    while(TOT--)
    {
        read(n),read(m);
        for(int i=1;i<=n;++i) read(a[i]);
        for(int i=1;i<=m;++i)
        {
            read(b[i].l),read(b[i].r);
            d[i]=1;
        }
        for(int i=1;i<=n;++i) g1[i]=n+1,g2[i]=0,g3[i]=0,g4[i]=n+1;
        for(int i=0;i<=30;++i) g[i]=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=0;j<=30;++j)
            {
                if(a[i]&(1<<j)) g1[i]=min(g1[i],g[j]);
                else g2[i]=max(g2[i],g[j]+1);
            }
            for(int j=0;j<=30;++j)
            {
                if(a[i]&(1<<j)) g[j]=i;
            }
        }
        for(int i=0;i<=30;++i) g[i]=n+1;
        for(int i=n;i>=1;--i)
        {
            for(int j=0;j<=30;++j)
            {
                if(a[i]&(1<<j)) g3[i]=max(g3[i],g[j]);
                else g4[i]=min(g4[i],g[j]-1);
            }
            for(int j=0;j<=30;++j)
            {
                if(a[i]&(1<<j)) g[j]=i;
            }
        }
        solve();
        for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
        for(int i=1;i<=m;++i) b[i].l=n-b[i].l+1,b[i].r=n-b[i].r+1,swap(b[i].l,b[i].r);
        for(int i=1;i<=n;++i)
        {
            g1[i]=n-g1[i]+1;
            g2[i]=n-g2[i]+1;
            g3[i]=n-g3[i]+1;
            g4[i]=n-g4[i]+1;
            swap(g1[i],g3[i]);
            swap(g2[i],g4[i]);
        }
        for(int i=1;i<=n/2;++i) swap(g1[i],g1[n-i+1]),swap(g2[i],g2[n-i+1]),swap(g3[i],g3[n-i+1]),swap(g4[i],g4[n-i+1]);
        solve();
        for(int i=1;i<=m;++i)
        {
            print(d[i]);
            putchar('\n');
        }
    }
    return 0;
}