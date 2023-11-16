#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=11;
int n,a[N];
ll f[N][10][2];
ll dfs(int x,int k,bool u)
{
    if(x==n+1) return 1;
    ll &f0=f[x][k][u];
    if(f0!=-1) return f0;
    f0=0;
    int t=u?a[x]:9;
    for(int i=0;i<=t;++i)
    {
        if(i==4||(k==6&&i==2)) continue;
        f0+=dfs(x+1,i,u&&i==t);
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
    memset(f,-1,sizeof(f));
    ll s=0;
    s-=dfs(1,-1,true);
    n=0;
    while(y!=0)
    {
        a[++n]=y%10;
        y/=10;
    }
    for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
    memset(f,-1,sizeof(f));
    s+=dfs(1,-1,true);
    printf("%lld\n",s);
    return 0;
}