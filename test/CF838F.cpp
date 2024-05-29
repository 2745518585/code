#include<cstdio>
#include<algorithm>
using namespace std;
const int N=20001;
int n;
double k,a[N],f[2][N],g[2][N];
int main()
{
    scanf("%d%lf",&n,&k);
    k/=1e6;
    for(int i=0;i<=n;++i)
    {
        scanf("%lf",&a[i]);
    }
    for(int i=0;i<=n;++i) g[n&1][i]=a[i];
    for(int i=n-1;i>=0;--i)
    {
        int t=i&1;
        for(int j=0;j<=i;++j)
        {
            g[t][j]=g[t^1][j+1]*(j+1)/(i+1)+g[t^1][j]*(i+1-j)/(i+1);
            if(g[t][j]!=0)
            {
                double w=g[t^1][j+1]*(j+1)/g[t][j]/(i+1);
                f[t][j]=max((f[t^1][j+1]+1)*w+(1-w)*f[t^1][j]-k,0.0);
            }
        }
    }
    printf("%.10lf",f[0][0]);
    return 0;
}