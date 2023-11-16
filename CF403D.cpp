#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001;
const ll P=1e9+7;
int m;
ll f[N][N],g[N][N],jc[N],C[N][N];
void init_jc(int x)
{
    jc[0]=1;
    for(int i=1;i<=x;++i) jc[i]=(jc[i-1]*i)%P;
}
int main()
{
    init_jc(1000);
    f[0][0]=1;
    for(int i=1;i<=1000;++i)
    {
        for(int j=i*(i+1)/2;j<=1000;++j)
        {
            f[i][j]=(f[i][j-i]+f[i-1][j-i])%P;
        }
    }
    C[0][0]=1;
    for(int i=1;i<=1000;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=1000;++j)
        {
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
        }
    }
    for(int i=1;i<=1000;i++)
    {
        for(int k=1;k<=50;k++)
        {
            for(int j=k*(k+1)/2;j<=i;j++)
            {
                g[i][k]=(g[i][k]+C[i-j+k][k]*f[k][j]%P)%P;
            }
            g[i][k]=g[i][k]*jc[k]%P;
        }
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(y>50) printf("0\n");
        else printf("%lld\n",g[x][y]);
    }
    return 0;
}