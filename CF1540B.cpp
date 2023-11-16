#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=1e9+7;
int n,m,q,p=1,t[N],h[N],g[N][N],d[N];
ll f[N][N];
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
    x=(x%P+P)%P;
    return x;
}
void dfs(int x,int fa)
{
    d[x]=d[fa]+1;
    int q1=q,q2=q;
    h[++q]=x;
    ++q2;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
        for(int j=q1+1;j<=q2;++j)
        {
            for(int k=q2+1;k<=q;++k) g[h[j]][h[k]]=g[h[k]][h[j]]=x;
        }
        q2=q;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) f[0][i]=1,f[i][0]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) f[i][j]=(f[i-1][j]+f[i][j-1])*inv(2)%P;
    }
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        q=0;
        dfs(i,0);
        ll w=0;
        for(int j=1;j<=n;++j)
        {
            for(int k=1;k<=j-1;++k)
            {
                w=(w+f[d[j]-d[g[j][k]]][d[k]-d[g[j][k]]])%P;
            }
        }
        s=(s+w*inv(n)%P)%P;
    }
    printf("%lld",s);
    return 0;
}