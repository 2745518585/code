#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=20,M=201;
int n,a[N],p;
ll f[N][M][M][2];
ll dfs(int x,int k,int w,bool u)
{
    if(x==n+1) return k==p&&w==0;
    if(k>p) return 0;
    ll &f0=f[x][k][w][u];
    if(f0!=-1) return f0;
    f0=0;
    int t=u?a[x]:9;
    for(int i=0;i<=t;++i)
    {
        f0+=dfs(x+1,k+i,(w*10+i)%p,u&&i==t);
    }
    return f0;
}
int main()
{
    ll x,y;
    scanf("%lld%lld",&x,&y);
    --x;
    n=0;
    while(x!=0)
    {
        a[++n]=x%10;
        x/=10;
    }
    if(n==0)
    {
        n=1;
        a[1]=0;
    }
    for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
    ll s=0;
    for(p=1;p<=9*n;++p)
    {
        memset(f,-1,sizeof(f));
        s-=dfs(1,0,0,true);
    }
    n=0;
    while(y!=0)
    {
        a[++n]=y%10;
        y/=10;
    }
    for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
    for(p=1;p<=9*n;++p)
    {
        memset(f,-1,sizeof(f));
        s+=dfs(1,0,0,true);
    }
    printf("%lld",s);
    return 0;
}