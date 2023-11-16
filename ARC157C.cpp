#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5001;
const ll P=998244353;
int m,n;
char a[N][N];
ll C[N][N],f[N][N],g[N][N],h[N][N];
int main()
{
    scanf("%d%d",&m,&n);
    C[0][0]=1;
    for(int i=1;i<=m+n;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
        }
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%s",a[i]+1);
    }
    h[1][1]=1;
    ll s=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==1&&j==1) continue;
            ll x1=f[i-1][j],y1=g[i-1][j],z1=h[i-1][j];
            if(a[i-1][j]=='Y'&&a[i][j]=='Y')
            {
                x1=(x1+y1*(z1-1)%P+(z1*(z1-1)/2)%P)%P;
                y1=(y1+z1)%P;
            }
            ll x2=f[i][j-1],y2=g[i][j-1],z2=h[i][j-1];
            if(a[i][j-1]=='Y'&&a[i][j]=='Y')
            {
                x2=(x2+y2*(z2-1)%P+(z2*(z2-1)/2)%P)%P;
                y2=(y2+z2)%P;
            }
            f[i][j]=(x1+x2+y1*y2)%P;
            g[i][j]=(y1+y2)%P;
            h[i][j]=(z1+z2)%P;
        }
    }
    printf("%lld",((g[m][n]*g[m][n]%P-f[m][n]*2)%P+P)%P);
    return 0;
}