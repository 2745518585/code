#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,k,a[N],b[N];
double sum(int x)
{
    return (double)((b[x]/k)-((a[x]-1)/k))/(b[x]-a[x]+1);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i],&b[i]);
    }
    a[n+1]=a[1],b[n+1]=b[1];
    double s=0;
    for(int i=1;i<=n;++i)
    {
        s+=sum(i)*2000+sum(i+1)*2000-sum(i)*sum(i+1)*2000;
    }
    printf("%.12lf",s);
    return 0;
}