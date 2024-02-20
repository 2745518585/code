#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=61;
const ll P=1e9+7;
int n,m;
ll f[N][N][N*N];
int main()
{
    scanf("%d%d",&n,&m);
    f[0][0][0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=i;++j)
        {
            for(int k=j*2;k<=n*n;++k)
            {
                f[i][j][k]=(f[i][j][k]+f[i-1][j][k-j*2])%P;
                f[i][j][k]=(f[i][j][k]+(j*2)*f[i-1][j][k-j*2]%P)%P;
                f[i][j][k]=(f[i][j][k]+(j+1)*(j+1)%P*f[i-1][j+1][k-j*2]%P)%P;
                if(j>=1) f[i][j][k]=(f[i][j][k]+f[i-1][j-1][k-j*2]%P)%P;
            }
        }
    }
    printf("%lld",(f[n][0][m]%P+P)%P);
    return 0;
}