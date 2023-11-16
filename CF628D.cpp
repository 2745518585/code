#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=3001;
const ll P=1e9+7;
int n,m,d,a[N];
ll l,r,f[N][N][2];
char z[N];
ll dfs(int x,int k,bool u)
{
    if(x==n+1) return k==0;
    ll &f0=f[x][k][u];
    if(f0!=-1) return f0;
    f0=0;
    int t=u?a[x]:9;
    for(int i=0;i<=t;++i)
    {
        if((x%2==0)^(i==d)) continue;
        f0=(f0+dfs(x+1,(k*10+i)%m,u&&i==t))%P;
    }
    return f0;
}
int main()
{
    scanf("%d%d",&m,&d);
    scanf("%s",z+1);
    n=strlen(z+1);
    for(int i=1;i<=n;++i) a[i]=z[i]-'0';
    --a[n];
    for(int i=n;i>=1;--i)
    {
        if(a[i]<0) a[i]+=10,--a[i-1];
        else break;
    }
    if(n==0)
    {
        n=1;
        a[1]=0;
    }
    memset(f,-1,sizeof(f));
    ll s=0;
    s-=dfs(1,0,true);
    scanf("%s",z+1);
    n=strlen(z+1);
    for(int i=1;i<=n;++i) a[i]=z[i]-'0';
    for(int i=n;i>=1;--i)
    {
        if(a[i]<0) a[i]+=10,--a[i-1];
        else break;
    }
    memset(f,-1,sizeof(f));
    s+=dfs(1,0,true);
    printf("%lld\n",(s%P+P)%P);
    return 0;
}