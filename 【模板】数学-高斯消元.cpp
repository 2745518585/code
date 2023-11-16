#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1001;
int n;
double a[N][N],b[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%lf",&a[i][j]);
        }
        scanf("%lf",&b[i]);
    }
    for(int i=1;i<=n;++i)
    {
        int k=i;
        for(int j=i+1;j<=n;++j)
        {
            if(fabs(a[j][i])>fabs(a[k][i])) k=j;
        }
        for(int j=1;j<=n;++j) swap(a[i][j],a[k][j]);
        swap(b[i],b[k]);
        if(a[i][i]==0)
        {
            printf("No Solution");
            return 0;
        }
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            double z=a[j][i]/a[i][i];
            b[j]-=b[i]*z;
            for(int l=i+1;l<=n;++l) a[j][l]-=a[i][l]*z;
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%.2lf\n",b[i]/a[i][i]);
    }
    return 0;
}