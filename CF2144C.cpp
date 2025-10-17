#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,a[N][2];
ll f[N][2];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i][0]);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i][1]);
        }
        for(int i=0;i<=n;++i) f[i][0]=f[i][1]=0;
        f[0][0]=1;
        for(int i=1;i<=n;++i)
        {
            if(a[i][0]>=a[i-1][0]&&a[i][1]>=a[i-1][1])
            {
                f[i][0]=(f[i][0]+f[i-1][0])%P;
                f[i][1]=(f[i][1]+f[i-1][1])%P;
            }
            if(a[i][0]>=a[i-1][1]&&a[i][1]>=a[i-1][0])
            {
                f[i][0]=(f[i][0]+f[i-1][1])%P;
                f[i][1]=(f[i][1]+f[i-1][0])%P;
            }
        }
        printf("%lld\n",(f[n][0]+f[n][1])%P);
    }
    return 0;
}