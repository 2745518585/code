#include<cstdio>
#include<algorithm>
using namespace std;
const int N=21;
int n,m,k;
double a[N],b[N],f[1<<N];
int sum(int x)
{
    int s=0;
    while(x)
    {
        x-=(x&-x);
        ++s;
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lf",&a[i]);
        if(a[i]>0) ++k;
    }
    if(k<=m)
    {
        for(int i=1;i<=n;++i)
        {
            if(a[i]>0) printf("1.00 ");
            else printf("0.00 ");
        }
        return 0;
    }
    f[0]=1;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        if(sum(i)>=m) continue;
        double w=0;
        for(int j=1;j<=n;++j)
        {
            if((i&(1<<(j-1)))==0) w+=a[j];
        }
        for(int j=1;j<=n;++j)
        {
            if((i&(1<<(j-1)))==0)
            {
                f[i|(1<<(j-1))]+=f[i]*a[j]/w;
            }
        }
    }
    for(int i=0;i<=(1<<n)-1;++i)
    {
        if(sum(i)!=m) continue;
        for(int j=1;j<=n;++j)
        {
            if((i&(1<<(j-1)))!=0) b[j]+=f[i];
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%.16lf ",b[i]);
    }
    return 0;
}