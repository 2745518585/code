#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,k,b[N],f[N],mu[N],val[N],mx[N];
ll g[N];
vector<int> a[N],d[N],e[N];
vector<pair<int,int>> c[N];
struct tree
{
    int f,s,z;
}T[N];
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void init()
{
    static int sp,p[N];
    static bool ip[N];
    mu[1]=1;
    val[1]=1;
    for(int i=2;i<=n;++i)
    {
        if(ip[i]==false) p[++sp]=i,mu[i]=-1,val[i]=-1;
        for(int j=1;j<=sp&&i*p[j]<=n;++j)
        {
            ip[i*p[j]]=true;
            val[i*p[j]]=-val[i];
            if(i%p[j]==0) break;
            mu[i*p[j]]=-mu[i];
        }
    }
    for(int i=1;i<=sp;++i)
    {
        int w=1;
        for(int j=1;;++j)
        {
            if(w>n/p[i]) break;
            w*=p[i];
            for(int l=1;w*l<=n;++l) mx[w*l]=max(mx[w*l],j);
        }
    }
}
void dfs0(int x)
{
    T[x].s=1;
    for(auto i:a[x])
    {
        if(i==T[x].f) continue;
        T[i].f=x;
        dfs0(i);
        T[x].s+=T[i].s;
        if(T[i].s>T[T[x].z].s) T[x].z=i;
    }
}
void dfs(int x)
{
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        dfs(i);
        g[x]+=g[i];
        for(auto j:e[i])
        {
            for(auto l:d[j]) f[l]=0;
        }
    }
    if(T[x].z)
    {
        dfs(T[x].z);
        g[x]+=g[T[x].z];
        swap(e[x],e[T[x].z]);
    }
    auto add=[&](vector<int> p)
    {
        for(auto v:p)
        {
            e[x].push_back(v);
            for(auto i:c[v])
            {
                g[x]+=val[v]*mu[i.first]*f[i.second];
            }
        }
        for(auto v:p)
        {
            for(auto i:d[v]) f[i]+=val[v];
        }
    };
    if(mx[b[x]]<=k/2) g[x]+=val[b[x]]*val[b[x]];
    if(mx[b[x]]<=k) add({b[x]});
    for(auto i:a[x])
    {
        if(i==T[x].f||i==T[x].z) continue;
        add(e[i]);
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    init();
    for(int i=1;i<=n;++i)
    {
        for(int j=1;i*j<=n;++j) d[i*j].push_back(i);
    }
    for(int i=1;i<=n;++i)
    {
        for(auto j:d[i])
        {
            ll w=1;
            for(int l=1;l<=k+1;++l)
            {
                w*=j;
                if(w>(ll)n*n) break;
            }
            w/=gcd(w,i);
            if(w<=n) c[i].push_back(make_pair(j,w));
        }
    }
    dfs0(1);
    dfs(1);
    for(int i=1;i<=n;++i)
    {
        printf("%lld\n",g[i]);
    }
    return 0;
}