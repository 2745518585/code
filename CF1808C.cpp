#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
#define X x][u1][u2][v
int a[21],b[21],k,f[21][2][2][2];
ll g[21][2][2][2],pow10[21];
int dfs(int x,int u1,int u2,int v)
{
    if(x==0) return 1e9;
    if(f[X]!=-1) return f[X];
    f[X]=-1e9;
    int t1=u1?a[x]:0,t2=min(u2?b[x]:9,k);
    for(int i=t1;i<=t2;++i)
    {
        int z=dfs(x-1,u1&&i==a[x],u2&&i==b[x],v&&i==0);
        if(!(v&&i==0)) z=min(z,i);
        if(z>f[X])
        {
            f[X]=z;
            g[X]=g[x-1][u1&&i==a[x]][u2&&i==b[x]][v&&i==0]+pow10[x-1]*i;
        }
    }
    return f[X];
}
int main()
{
    pow10[0]=1;
    for(int i=1;i<=18;++i) pow10[i]=pow10[i-1]*10;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ll x,y;
        scanf("%lld%lld",&x,&y);
        for(int i=0;i<=19;++i) a[i]=b[i]=0;
        int z=0;
        while(x) a[++z]=x%10,x/=10;
        z=0;
        while(y) b[++z]=y%10,y/=10;
        int s=1e9;
        ll q=0;
        for(k=0;k<=9;++k)
        {
            memset(f,-1,sizeof(f));
            memset(g,0,sizeof(g));
            int z=dfs(19,true,true,true);
            if(k-z<s)
            {
                s=k-z;
                q=g[19][1][1][1];
            }
        }
        printf("%lld\n",q);
    }
    return 0;
}