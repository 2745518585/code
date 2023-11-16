#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const ll P=1e9+7;
int n,a[21];
ll pow10[21],f[21][11][11][2],g[21][11][11][2],h[21][11][11][2];
#define X x][k1][k2][u
#define Y x-1][(k1+i)%7][(k2*10+i)%7][u&&i==t
void dfs(int x,int k1,int k2,bool u)
{
    if(x==0)
    {
        f[X]=g[X]=0;
        h[X]=k1%7!=0&&k2%7!=0;
        return;
    }
    if(f[X]!=-1) return;
    f[X]=g[X]=h[X]=0;
    int t=u?a[x]:9;
    for(int i=0;i<=t;++i)
    {
        if(i==7) continue;
        dfs(x-1,(k1+i)%7,(k2*10+i)%7,u&&i==t);
        h[X]=(h[X]+h[Y])%P;
        g[X]=(g[X]+g[Y]+h[Y]*(i*pow10[x-1]%P)%P)%P;
        f[X]=(f[X]+f[Y]+2*g[Y]*(i*pow10[x-1]%P)%P+h[Y]*((i*pow10[x-1]%P)%P*(i*pow10[x-1]%P)%P)%P)%P;
    }
}
int main()
{
    pow10[0]=1;
    for(int i=1;i<=18;++i) pow10[i]=pow10[i-1]*10%P;
    int T;
    scanf("%d",&T);
    while(T--)
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
        if(n==0) n=1,a[1]=0;
        memset(f,-1,sizeof(f));
        memset(g,-1,sizeof(g));
        memset(h,-1,sizeof(h));
        ll s=0;
        dfs(n,0,0,true);
        s-=f[n][0][0][1];
        n=0;
        while(y!=0)
        {
            a[++n]=y%10;
            y/=10;
        }
        memset(f,-1,sizeof(f));
        memset(g,-1,sizeof(g));
        memset(h,-1,sizeof(h));
        dfs(n,0,0,true);
        s+=f[n][0][0][1];
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}