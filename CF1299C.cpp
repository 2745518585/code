#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,d[N];
ll a[N],b[N];
double c[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        b[i]=b[i-1]+a[i];
        d[i]=i;
    }
    d[n+1]=n+1;
    for(int i=n;i>=1;--i)
    {
        int x=i;
        while(d[x+1]<=n&&(b[d[x+1]]-b[i-1])*(x-i+1)<=(b[x]-b[i-1])*(d[x+1]-i+1)) x=d[x+1];
        c[i]=(double)(b[x]-b[i-1])/(x-i+1);
        d[i]=x;
    }
    for(int i=1;i<=n;++i) c[i]=max(c[i-1],c[i]);
    for(int i=1;i<=n;++i)
    {
        printf("%.9lf\n",c[i]);
    }
    return 0;
}