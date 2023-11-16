#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=201;
const ll P=998244353;
int n,k,b[N];
ll s,jc[N],ivjc[N],f[N][N][N],h[N][N];
vector<int> a[N];
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
    b[x]=1;
    f[x][1][0]=1;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
        for(int j=0;j<=b[x];++j)
        {
            for(int k=0;k<=b[x];++k) h[j][k]=f[x][j][k],f[x][j][k]=0;
        }
        for(int j=0;j<=b[x];++j)
        {
            for(int k=0;k<=b[x];++k)
            {
                f[x][j][k+1]=(f[x][j][k+1]+h[j][k])%P;
            }
        }
        for(int j1=0;j1<=b[x];++j1)
        {
            for(int j2=0;j2<=b[i];++j2)
            {
                for(int k1=0;k1<=b[x];++k1)
                {
                    for(int k2=0;k2<=b[i];++k2)
                    {
                        f[x][j1+j2][k1+k2]=(f[x][j1+j2][k1+k2]+h[j1][k1]*f[i][j2][k2]%P)%P;
                    }
                }
            }
        }
        b[x]+=b[i];
    }
    for(int i=k+1;i<=b[x];++i)
    {
        for(int j=0;j<=b[x];++j)
        {
            s=(s+f[x][i][j]*jc[i]%P*jc[j+(fa!=0)]%P*ivjc[i+j+(fa!=0)]%P)%P;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    jc[0]=1;
    for(int i=1;i<=n*2;++i) jc[i]=jc[i-1]*i%P;
    for(int i=0;i<=n*2;++i) ivjc[i]=inv(jc[i]);
    dfs(1,0);
    printf("%lld\n",s);
    return 0;
}