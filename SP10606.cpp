#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=20,M=10;
int n,a[N];
ll f[N][1<<M][1<<M][2][2];
ll dfs(int x,int k,int q,bool u,bool v)
{
    if(x==n+1) return (k&q)==(q&341);
    ll &f0=f[x][k][q][u][v];
    if(f0!=-1) return f0;
    f0=0;
    int t=u?a[x]:9;
    for(int i=0;i<=t;++i)
    {
        f0+=dfs(x+1,(v&&i==0)?k:k^(1<<i),(v&&i==0)?q:q|(1<<i),u&&i==t,v&&i==0);
    }
    return f0;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ull x,y;
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
        ll s1=dfs(1,0,0,true,true);
        n=0;
        while(y!=0)
        {
            a[++n]=y%10;
            y/=10;
        }
        for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
        memset(f,-1,sizeof(f));
        ll s2=dfs(1,0,0,true,true);
        printf("%lld\n",s2-s1);
    }
    return 0;
}