#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
int n,m;
ll P,f[N][N][2],g[N][2],h[N][2];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%lld",&n,&m,&P);
        for(int i=0;i<=n+1;++i)
        {
            for(int j=0;j<=n+1;++j) f[i][j][0]=f[i][j][1]=0;
        }
        f[0][0][0]=1;
        for(int i=1;i<=n+1;++i)
        {
            ll w1=0,w2=0;
            for(int j=0;j<=m;++j)
            {
                w1=(w1+f[i-1][j][0])%P;
                w2=(w2+f[i-1][j][1])%P;
            }
            for(int j=0;j<=m;++j)
            {
                f[i][j][0]=w1;
                f[i][j][1]=w2;
            }
            if(i>1)
            {
                g[0][0]=f[i-2][0][0],g[0][1]=f[i-2][0][1];
                h[0][0]=h[0][1]=0;
                for(int j=1;j<=m;++j)
                {
                    g[j][0]=(g[j-1][0]+f[i-2][j][0])%P;
                    g[j][1]=(g[j-1][1]+f[i-2][j][1])%P;
                    h[j][0]=(h[j-1][0]+f[i-2][j][0]*j%P)%P;
                    h[j][1]=(h[j-1][1]+f[i-2][j][1]*j%P)%P;
                }
                for(int j=0;j<=m;++j)
                {
                    for(int k=0;k<=1;++k)
                    {
                        f[i][j][k]=(f[i][j][k]+g[m-j][k^1]*(m-j)%P-h[m-j][k^1])%P;
                    }
                }
            }
        }
        printf("%lld\n",((f[n+1][0][0]-f[n+1][0][1])%P+P)%P);
    }
    return 0;
}