#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=998244353;
int n;
ll f[N][N],a[N];
ll solve(int x)
{
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=n;++j) f[i][j]=0;
    }
    f[0][0]=1;
    for(int i=1;i<=x-1;++i)
    {
        for(int j=0;j<=n;++j)
        {
            f[i][j]=(f[i][j]+f[i-1][j])%P;
            if(a[i]>=0)
            {
                if(a[i]<=a[x]) f[i][j+1]=(f[i][j+1]+f[i-1][j])%P;
                else f[i][j]=(f[i][j]+f[i-1][j])%P;
            }
            else f[i][max(j-1,0)]=(f[i][max(j-1,0)]+f[i-1][j])%P;
        }
    }
    for(int i=0;i<=n;++i)
    {
        f[x][i]=(f[x][i]+f[x-1][i])%P;
    }
    for(int i=x+1;i<=n;++i)
    {
        for(int j=0;j<=n;++j)
        {
            f[i][j]=(f[i][j]+f[i-1][j])%P;
            if(a[i]>=0)
            {
                if(a[i]<a[x]) f[i][j+1]=(f[i][j+1]+f[i-1][j])%P;
                else f[i][j]=(f[i][j]+f[i-1][j])%P;
            }
            else if(j>=1) f[i][j-1]=(f[i][j-1]+f[i-1][j])%P;
        }
    }
    ll s=0;
    for(int i=0;i<=n;++i) s=(s+f[n][i])%P;
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='-') a[i]=-1;
        else scanf("%lld",&a[i]);
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]>=0) s=(s+(ll)solve(i)*a[i]%P)%P;
    }
    printf("%lld",s);
    return 0;
}