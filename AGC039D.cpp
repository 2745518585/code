#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long double ld;
const int N=5001;
const ld pi=acos(-1.0);
int n,m,a[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    ld s1=0,s2=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            ld t=pi*(a[i]+a[j])/m;
            s1-=cos(t)*(j-i-1);
            s2-=sin(t)*(j-i-1);
            s1+=cos(t)*(n-(j-i+1));
            s2+=sin(t)*(n-(j-i+1));
        }
    }
    printf("%.18Lf %.18Lf",s1/((ld)n*(n-1)*(n-2)/6),s2/((ld)n*(n-1)*(n-2)/6));
    return 0;
}