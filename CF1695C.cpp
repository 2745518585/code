#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;
const int N=2001;
int m,n,a[N][N];
bitset<N> f[N],g[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                scanf("%d",&a[i][j]);
            }
        }
        if((m+n)%2==0)
        {
            printf("NO\n");
            continue;
        }
        for(int i=1;i<=n;++i) f[i]=0;
        f[1][0]=1;
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j) g[j]=f[j],f[j]=0;
            for(int j=1;j<=n;++j)
            {
                if(a[i][j]==1) f[j]|=(f[j-1]<<1)|(g[j]<<1);
                else f[j]|=f[j-1]|g[j];
            }
        }
        if(f[n][(m+n-1)/2]==1) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}