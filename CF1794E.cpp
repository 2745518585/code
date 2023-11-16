#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,p=1,t[N],b[N];
bool h[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
struct Solve
{
    ll B,powb[N],w,f[N],g[N];
    set<ll> Set;
    void dfs1(int x,int fa)
    {
        f[x]=1;
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(a[i].m==fa) continue;
            dfs1(a[i].m,x);
            f[x]=(f[x]+f[a[i].m]*B%P)%P;
        }
    }
    void dfs2(int x,int fa)
    {
        for(int i=t[x];i!=0;i=a[i].q)
        {
            if(a[i].m==fa) continue;
            g[a[i].m]=(f[x]+g[x]-f[a[i].m]*B%P)*B%P;
            dfs2(a[i].m,x);
        }
    }
    void main()
    {
        powb[0]=1;
        for(int i=1;i<=n;++i) powb[i]=powb[i-1]*B%P;
        for(int i=1;i<=n-1;++i)
        {
            w=(w+powb[b[i]])%P;
        }
        for(int i=0;i<=n;++i)
        {
            Set.insert((w+powb[i])%P);
        }
        dfs1(1,0);
        dfs2(1,0);
        int s=0;
        for(int i=1;i<=n;++i)
        {
            if(!Set.count(((f[i]+g[i])%P+P)%P)) h[i]=false;
        }
    }
}solve1,solve2,solve3;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=n;++i) h[i]=true;
    solve1.B=12,solve2.B=1234,solve3.B=1234567;
    solve1.main();
    solve2.main();
    solve3.main();
    int s=0;
    for(int i=1;i<=n;++i) s+=h[i];
    printf("%d\n",s);
    for(int i=1;i<=n;++i)
    {
        if(h[i]) printf("%d ",i);
    }
    return 0;
}