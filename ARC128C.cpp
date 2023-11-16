#include<cstdio>
#include<algorithm>
using namespace std;
typedef long double ld;
const int N=1000001;
int n;
ld m,k,a[N];
int main()
{
    scanf("%d%Lf%Lf",&n,&m,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%Lf",&a[i]);
    }
    for(int i=n;i>=1;--i) a[i]+=a[i+1];
    int t=n+1;
    while(true)
    {
        int x=1;
        for(int j=1;j<=t-1;++j)
        {
            if((a[j]-a[t])/(t-j)>(a[x]-a[t])/(t-x)) x=j;
        }
        if((ld)(t-x)*m<k)
        {
            k-=(ld)(t-x)*m;
            t=x;
        }
        else
        {
            printf("%.15Lf",k/(t-x)*(a[x]-a[t])+m*a[t]);
            return 0;
        }
    }
    return 0;
}