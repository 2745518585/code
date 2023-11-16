#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=924844033;
int n,k;
ll C[N][N],f[N][N][2],g[N],jc[N];
bool h[N];
int main()
{
    scanf("%d%d",&n,&k);
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    C[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=n;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    int z=0;
    h[0]=true;
    for(int i=1;i<=k;++i)
    {
        h[z+=((n-i)/k+1)]=true;
        h[z+=((n-i)/k+1)]=true;
    }
    f[0][0][0]=1;
    for(int i=1;i<=n*2;++i)
    {
        for(int j=0;j<=n;++j)
        {
            f[i][j][0]=(f[i-1][j][0]+f[i-1][j][1])%P;
            if(j>=1&&h[i-1]==false) f[i][j][1]=f[i-1][j-1][0];
        }
    }
    for(int i=0;i<=n;++i)
    {
        g[i]=(f[n*2][i][0]+f[n*2][i][1])%P*jc[n-i]%P;
    }
    ll s=0;
    for(int i=0;i<=n;++i)
    {
        if(i%2==0) s=(s+g[i])%P;
        else s=(s-g[i])%P;
    }
    printf("%lld",(s%P+P)%P);
    return 0;
}