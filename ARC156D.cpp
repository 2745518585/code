#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
int n,a[N];
ll m,f[61][N],g[61][N];
bool h[61][N];
int main()
{
    scanf("%d%lld",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    f[0][0]=0,g[0][0]=1,h[0][0]=true;
    for(int i=0;i<=50;++i)
    {
        for(int j=0;j<=3000;++j)
        {
            if(h[i][j]==false) continue;
            if(m&(1ll<<i))
            {
                for(int k=1;k<=n;++k)
                {
                    f[i+1][a[k]+j/2]^=f[i][j];
                    g[i+1][a[k]+j/2]^=g[i][j];
                    h[i+1][a[k]+j/2]=true;
                    if(g[i][j]%2==1&&j%2==1) f[i+1][a[k]+j/2]^=(1ll<<(i-1));
                }
            }
            else
            {
                f[i+1][j/2]^=f[i][j];
                g[i+1][j/2]^=g[i][j];
                if(g[i][j]%2==1&&j%2==1) f[i+1][j/2]^=(1ll<<(i-1));
                h[i+1][j/2]=true;
            }
        }
    }
    printf("%lld\n",f[51][0]);
    return 0;
}