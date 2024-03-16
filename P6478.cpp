#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=6001;
const ll P=998244353;
int n,m,d[N],d1[N],d2[N];
char b[N];
vector<int> a[N];
ll f[N][N],C[N][N],jc[N];
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
    d[x]=1;
    if(b[x]=='0') d1[x]=1;
    else d2[x]=1;
    f[x][0]=1;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
        for(int j=d[x];j>=0;--j)
        {
            for(int k=1;k<=d[i];++k)
            {
                f[x][j+k]=(f[x][j+k]+f[x][j]*f[i][k]%P)%P;
            }
        }
        d[x]+=d[i];
        d1[x]+=d1[i];
        d2[x]+=d2[i];
    }
    for(int i=d[x];i>=0;--i)
    {
        if(b[x]=='0') f[x][i+1]=(f[x][i+1]+f[x][i]*(d2[x]-i)%P)%P;
        else f[x][i+1]=(f[x][i+1]+f[x][i]*(d1[x]-i)%P)%P;
    }
}
int main()
{
    scanf("%d%s",&n,b+1);
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs(1,0);
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    for(int i=0;i<=n/2;++i)
    {
        ll s=0;
        for(int j=i;j<=n/2;++j)
        {
            if((j-i)%2) s=(s-C[j][i]*jc[n/2-j]%P*f[1][j]%P)%P;
            else s=(s+C[j][i]*jc[n/2-j]%P*f[1][j]%P)%P;
        }
        printf("%lld\n",(s%P+P)%P);
    }
    return 0;
}