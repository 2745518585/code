#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=9901;
int n,m;
ll f[N][N],g[N][N];
int main()
{
    scanf("%d%d",&n,&m);
    f[1][1]=1;
    for(int i=1;i<=m;++i) g[1][i]=1;
    for(int i=2;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            for(int k=1;k<=i-2;++k)
            {
                f[i][j]=(f[i][j]+f[k][j-1]*g[i-k-1][j-1]%P+g[k][j-2]*f[i-k-1][j-1]%P)%P;
            }
        }
        for(int j=1;j<=m;++j) g[i][j]=(g[i][j-1]+f[i][j])%P;
    }
    printf("%lld",f[n][m]);
    return 0;
}