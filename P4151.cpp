#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001;
int n,m,p=1,t[N];
ll b[N],f[N];
bool h[N];
struct road
{
    int m,q;
    ll w;
}a[N<<1];
void road(int x,int y,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void add(ll x)
{
    for(int i=60;i>=0;--i)
    {
        if((x&(1ll<<i))==0) continue;
        if(b[i]==0)
        {
            b[i]=x;
            return;
        }
        x^=b[i];
    }
}
void dfs(int x,ll w)
{
    h[x]=true;
    f[x]=w;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m])
        {
            add(f[a[i].m]^w^a[i].w);
            continue;
        }
        dfs(a[i].m,w^a[i].w);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll w;
        scanf("%d%d%lld",&x,&y,&w);
        road(x,y,w);
        road(y,x,w);
    }
    dfs(1,0);
    ll s=f[n];
    for(int i=60;i>=0;--i)
    {
        if((s^b[i])>s) s^=b[i];
    }
    printf("%lld",s);
    return 0;
}