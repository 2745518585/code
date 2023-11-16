#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef unsigned ui;
const int N=200001,M=501;
int n,m,q;
ui a[N],b[N],c[M][N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%u",&a[i]);
    }
    for(int i=1;i<=n;++i) b[i]=b[i-1]+a[i];
    q=sqrt(n);
    for(int i=1;i<=q;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(j<i) c[i][j]=a[j];
            else c[i][j]=c[i][j-i]+a[j];
        }
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x1,x2,d;
        scanf("%d%d%d",&d,&x1,&x2);
        ui s=0;
        for(int j=0;j<=d-1;++j)
        {
            s+=(c[d][x1+d*(d-1)+j]-(x1+j-d>=1?c[d][x1+j-d]:0))*(b[x2+d*j+(d-1)]-b[x2+d*j-1]);
        }
        printf("%u\n",s);
    }
    return 0;
}