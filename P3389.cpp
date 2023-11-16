#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1001;
int n;
double a[N][N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%lf",&a[i][j]);
        }
        scanf("%lf",&a[i][0]);
    }
    for(int i=1;i<=n;++i)
    {
        int k=i;
        for(int j=i+1;j<=n;++j)
        {
            if(fabs(a[j][i])>fabs(a[k][i])) k=i;
        }
        for(int j=1;j<=n;++j)
        {
            swap(a[i][j],a[k][j]);
        }
        if(a[i][i]==0)
        {
            printf("No Solution");
            return 0;
        }
        for(int j=1;j<=n;++j)
        {
            if(i==j) continue;
            double z=a[j][i]/a[i][i];
            a[j][0]-=a[i][0]*z;
            for(int l=i+1;l<=n;++l) a[j][l]-=a[i][l]*z;
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%.2lf\n",a[i][0]/a[i][i]);
    }
    return 0;
}