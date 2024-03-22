#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=301;
const ll P=1e9+7;
int n,a[N];
ll jc[N],f[N][N],g[N][N][N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    if(a[1]==n)
    {
        printf("0");
        return 0;
    }
    jc[0]=1;
    for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i%P;
    for(int i=1;i<=n;++i) g[i][i-1][0]=1;
    for(int i=n;i>=1;--i)
    {
        for(int j=i;j<=n;++j)
        {
            for(int k=0;k<=j-i+1;++k)
            {
                if(k>0) g[i][j][k]=g[i][j-1][k-1];
                for(int l=i+1;l<=j;++l)
                {
                    if(j<=a[l]) g[i][j][k]-=g[i][l-1][k]*f[l][j]%P;
                }
                g[i][j][k]%=P;
                f[i][j]=(f[i][j]+g[i][j][k]*jc[k]%P)%P;
            }
            if(j<=a[i]) g[i][j][0]=(g[i][j][0]-f[i][j])%P;
        }
    }
    printf("%lld",(f[1][n]%P+P)%P);
    return 0;
}