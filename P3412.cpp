#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,l[N],d[N];
ll f[N],g[N],s;
vector<int> a[N];
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x; 
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    return (x%P+P)%P;
}
void dfs1(int x,int fa)
{
    f[x]=l[x];
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs1(i,x);
        f[x]=(f[x]+f[i])%P;
    }
}
void dfs2(int x,int fa)
{
    for(auto i:a[x])
    {
        if(i==fa) continue;
        g[i]=(f[x]-f[i]+g[x]+P)%P;
        dfs2(i,x);
    }
}
void dfs3(int x,int fa)
{
    d[x]=1;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs3(i,x);
        d[x]+=d[i];
        s=(s+(ll)(n-d[i])*d[i]%P*(f[i]+g[i])%P)%P;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
        ++l[x],++l[y];
    }
    dfs1(1,0);
    dfs2(1,0);
    dfs3(1,0);
    printf("%lld",(s*inv((ll)n*n%P)%P+P)%P);
    return 0;
}