#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=998244353;
int n,m,k,a[N],b[N];
ll f[N][N][2],g[N][N][2],C[N][N];
bool cmp(int a,int b)
{
    return a>b;
}
void init()
{
    for(int i=0;i<=3000;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
}
int main()
{
    init();
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
        }
        sort(a+1,a+n+1,cmp);
        sort(b+1,b+n+1,cmp);
        f[0][0][0]=f[0][0][1]=1;
        for(int i=1;i<=n;++i)
        {
            f[i][0][1]=1;
            for(int j=1;j<=i;++j)
            {
                f[i][j][0]=(f[i-1][j-1][1]*a[i])%P;
                f[i][j][1]=(f[i][j][0]+f[i-1][j][1])%P;
            }
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=i;++j)
            {
                g[i][j][0]=(g[i-1][j-1][1]+C[i-1][j-1]*b[i])%P;
                g[i][j][1]=(g[i][j][0]+g[i-1][j][1])%P;
            }
        }
        ll s=0;
        for(int i=0;i<k-1;++i)
        {
            for(int j=1;j<=n;++j)
            {
                s=(s+f[n][i][1]*g[j][k-i][0]%P*C[n-j][m-k]%P)%P;
            }
        }
        for(int i=k-1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                s=(s+f[i][k-1][0]*b[j]%P*C[2*n-i-j][m-k]%P)%P;
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}