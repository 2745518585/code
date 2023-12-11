#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=101;
int n,k;
ll a[N][2],b[N],f[N][N][N][2][2][2][2];
ll dfs(int x,int l,int r,int tl,int pl,int tr,int pr)
{
    if(x==k) return l>r?0:1e18;
    ll &f0=f[x][l][r][tl][pl][tr][pr];
    if(f0!=-1) return f0;
    f0=dfs(x+1,l,r,tl,0,tr,0);
    if(l!=1&&r!=n&&((((a[l-1][tl]>>x)^pl)&1)^(((a[r+1][tr]>>x)^pr)&1))) f0+=b[x];
    for(int k=l;k<=r;++k)
    {
        for(int t=0;t<=1;++t)
        {
            if(x==0)
            {
                f0=min(f0,dfs(x,l,k-1,tl,pl,t,0)+dfs(x,k+1,r,t,0,tr,pr));
            }
            if(((a[k][t]^(1ll<<x))&(~((1ll<<x)-1)))>=a[k][0]&&((a[k][t]^(1ll<<x))|((1ll<<x)-1))<=a[k][1])
            {
                f0=min(f0,dfs(x,l,k-1,tl,pl,t,1)+dfs(x,k+1,r,t,1,tr,pr));
            }
        }
    }
    return f0;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&a[i][0],&a[i][1]);
    }
    for(int i=0;i<=k-1;++i)
    {
        scanf("%lld",&b[i]);
    }
    memset(f,-1,sizeof(f));
    printf("%lld",dfs(0,1,n,0,0,0,0));
    return 0;
}