#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=61,M=15;
const ll P=1e9+7;
int n,q,t,a[N],b[N],c[N],d[1<<M],w2=0;
ll f[1<<M][N],w1=1;
bool g[N],h[N];
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
void dfs(int x)
{
    h[x]=false;
    a[++q]=x;
    for(int i=1;i<=60;++i)
    {
        if(h[i]&&(i%x==0||x%i==0)) dfs(i);
    }
}
void solve(int x)
{
    q=t=0;
    for(int i=1;i<=60;++i) g[i]=false;
    dfs(x);
    sort(a+1,a+q+1);
    if(q==1) return;
    for(int i=1;i<=q;++i)
    {
        if([&]()
        {
            for(int j=1;j<=i-1;++j)
            {
                if(a[i]%a[j]==0) return false;
            }
            return true;
        }()) b[++t]=a[i];
        else g[i]=true;
    }
    for(int i=1;i<=q;++i)
    {
        if(!g[i]) continue;
        c[i]=0;
        for(int j=1;j<=t;++j)
        {
            if(a[i]%b[j]==0) c[i]|=(1<<(j-1));
        }
    }
    for(int i=0;i<=(1<<t)-1;++i)
    {
        d[i]=0;
        for(int j=1;j<=q;++j)
        {
            if(g[j]&&((c[j]&i)==c[j])) ++d[i];
        }
    }
    for(int i=0;i<=(1<<t)-1;++i)
    {
        for(int j=1;j<=q;++j) f[i][j]=0;
    }
    for(int i=1;i<=q;++i)
    {
        if(g[i]) f[c[i]][1]=(f[c[i]][1]+1)%P;
    }
    for(int i=0;i<=(1<<t)-1;++i)
    {
        for(int j=0;j<=q;++j)
        {
            f[i][j+1]=(f[i][j+1]+f[i][j]*(d[i]-j)%P)%P;
            for(int k=1;k<=q;++k)
            {
                if(g[k]&&(i&c[k])&&((i|c[k])>i)) f[i|c[k]][j+1]=(f[i|c[k]][j+1]+f[i][j])%P;
            }
        }
    }
    ll s=0;
    for(int i=0;i<=(1<<t)-1;++i) s=(s+f[i][q-t])%P;
    w1=w1*s%P;
    for(int i=1;i<=q-t-1;++i) w1=w1*inv(i)%P;
    w2+=q-t-1;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        h[x]=true;
    }
    for(int i=1;i<=60;++i)
    {
        if(h[i]) solve(i);
    }
    for(int i=1;i<=w2;++i) w1=w1*i%P;
    printf("%lld\n",w1);
    return 0;
}