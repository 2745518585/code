#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=11,M=100001;
const ll P=998244353;
int n,m,q,b[M][N];
ll L,a[N][N],c[N][N],d1[N],d2[N];
struct poly
{
    int n;
    ll a[21];
    poly()
    {
        for(int i=0;i<=20;++i) a[i]=0;
    }
    poly(ll x)
    {
        for(int i=0;i<=20;++i) a[i]=x;
    }
    poly(const vector<ll> &x)
    {
        for(int i=0;i<=20;++i)
        {
            ll w=1;
            for(int j=0;j<=x.size();++j) a[i]=(a[i]+x[j]*w%P)%P,w=w*i%P;
        }
    }
    ll &operator[](size_t pos) {return a[pos];}
    ll operator[](size_t pos) const {return a[pos];}
    ll operator()(ll x)
    {
        ll s=0,w=1;
        for(int i=0;i<=n;++i) s=(s+w*a[i]%P)%P,w=w*x%P;
        return s;
    }
    poly operator()(poly x)
    {
        poly s=0,w=1;
        for(int i=0;i<=n;++i) s=s+w*a[i],w=w*x;
        return s;
    }
    friend poly operator+(const poly &a,const poly &b)
    {
        poly c;
        for(int i=0;i<=20;++i) c[i]=(a[i]+b[i])%P;
        return c;
    }
    friend poly operator*(const poly &a,const poly &b)
    {
        poly c;
        for(int i=0;i<=20;++i) c[i]=a[i]*b[i]%P;
        return c;
    }
}f[N];
void dfs(int x)
{
    static int c[N];
    if(x==0)
    {
        ++q;
        for(int i=1;i<=n;++i) b[q][i]=c[i];
        return;
    }
    for(c[x]=0;c[x]<=x-1;++c[x]) dfs(x-1);
}
void check1(int p,int x,int y)
{
    if(x==0) d1[y]=max(d1[y],d2[p]-c[y][p]+(y<x));
    else if(y==0) d2[x]=min(d2[x],d2[p]-c[x][p]-(y<x));
    else c[x][y]=min(c[x][y],c[y][p]-c[x][p]-(y<x));
}
void check2(int p,int x,int y)
{
    if(x==0) d2[y]=min(d2[y],d1[p]+c[p][y]-(y<x));
    else if(y==0) d1[x]=max(d1[x],d1[p]+c[p][x]+(y<x));
    else c[y][x]=min(c[y][x],c[p][y]-c[p][x]-(y<x));
}
void check3(int p,int x,int y)
{
    if(x==0) d2[y]=min(d2[y],d2[p]+c[p][y]);
    else if(y==0) d1[x]=max(d1[x],d1[p]-c[x][p]);
    else if(x!=0&&y!=0) c[y][x]=min(c[y][x],c[p][y]+c[x][p]);
}
ll solve(int p,int t)
{
    for(int i=1;i<=n;++i) d1[i]=0,d2[i]=L,f[i]=poly({0,1});
    ll w=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) c[i][j]=a[i][j];
    }
    for(int i=n;i>=2;--i)
    {
        if((p&(1<<(i-1)))==0)
        {
            for(int j=0;j<=i-1;++j)
            {
                if(j!=b[t][i]) check1(i,b[t][i],j);
            }
            for(int j=0;j<=i-1;++j) check3(i,b[t][i],j);
            if(b[t][i]==0) w=w*d2[i]%P;
            else
            {
                f[b[t][i]]=f[b[t][i]]*f[i](poly({c[b[t][i]][i],1}));
            }
        }
        else
        {
            for(int j=0;j<=i-1;++j)
            {
                if(j!=b[t][i]) check2(i,b[t][i],j);
            }
            for(int j=0;j<=i-1;++j) check3(i,j,b[t][i]);
            if(b[t][i]==0) w=w*(d1[i]-1)%P;
            else
            {
                f[b[t][i]]=f[b[t][i]]*f[i](poly({-c[i][b[t][i]]-1,1}));
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(d1[i]>d2[i]||c[i][i]<0) return 0;
    }
    for(int i=1;i<=n;++i) printf("%d %d %d %lld %lld\n",i,(p&(1<<(i-1)))!=0,b[t][i],d1[i],d2[i]);
    for(int i=0;i<=f[1].n;++i) printf("%lld ",f[1][i]);printf("\n");
    printf("%lld %lld\n",w,(p&1)==0?w*f[1](d2[1])%P:w*f[1](d1[1]-1)%P);
    printf("\n");
    if((p&1)==0) return w*f[1](d2[1])%P;
    else return w*f[1](d1[1]-1)%P;
}
int popc(int x)
{
    int s=0;
    while(x) x^=x&-x,++s;
    return s;
}
int main()
{
    scanf("%d%d%lld",&n,&m,&L);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) a[i][j]=1e15;
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        a[y][x]=min(a[y][x],w);
    }
    dfs(n);
    ll s=0;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        ll w=0;
        for(int j=1;j<=q;++j)
        {
            w=(w+solve(i,j))%P;
        }
        if(popc(i)%2==0) s=(s+w)%P;
        else s=(s-w)%P;
    }
    printf("%lld",s);
    return 0;
}