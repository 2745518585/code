#include<cstdio>
#include<algorithm>
using namespace std;
const int N=101,M=15;
int n,m,a[N],b[N];
double f[N][1<<M];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&a[i]);
        int x;
        scanf("%d",&x);
        while(x!=0)
        {
            b[i]|=(1<<(x-1));
            scanf("%d",&x);
        }
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=0;j<=(1<<m)-1;++j)
        {
            for(int k=1;k<=m;++k)
            {
                if((j&b[k])==b[k])
                {
                    f[i][j]+=max(f[i+1][j],f[i+1][j|(1<<(k-1))]+a[k])/m;
                }
                else f[i][j]+=f[i+1][j]/m;
            }
        }
    }
    printf("%.6lf",f[1][0]);
    return 0;
}