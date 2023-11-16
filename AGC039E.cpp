#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=41;
int n;
ll f[N][N][N],g[N][N][N];
char a[N][N];
int main()
{
    scanf("%d",&n);
    n*=2;
    for(int i=1;i<=n;++i)
    {
        scanf("%s",a[i]+1);
    }
    for(int i=1;i<=n;++i)
    {
        f[i][i][i]=1;
        for(int j=1;j<=n;++j)
        {
            if(a[j][i]=='1') g[i][j][i]=1;
        }
    }
    for(int o=2;o<=n;++o)
    {
        for(int i=1,j=i+o-1;j<=n;++i,++j)
        {
            for(int p=i;p<=j;++p)
            {
                for(int q=p+2;q<=j;++q)
                {
                    ll w=0;
                    for(int k=q;k<=j;++k) w+=g[i][k][p]*f[q][k][j];
                    for(int k=p+1;k<=q-1;++k) f[i][k][j]+=f[p+1][k][q-1]*w;
                }
            }
            for(int k=1;k<=n;++k)
            {
                for(int l=i;l<=j;++l)
                {
                    if(a[k][l]=='1') g[i][k][j]+=f[i][l][j];
                }
            }
        }
    }
    ll s=0;
    for(int i=2;i<=n;++i)
    {
        if(a[1][i]=='1') s+=f[2][i][n];
    }
    printf("%lld",s);
    return 0;
}