#include<cstdio>
#include<algorithm>
using namespace std;
int a[10001],b[10001];
int main()
{
    int n,m=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        m+=a[i];
    }
    m/=n;
    int s=1e9;
    for(int i=1;i<=n;++i)
    {
        int w=0;
        for(int j=1;j<=n;++j)
        {
            b[j]=a[j];
        }
        for(int j=1;j<=n-1;++j)
        {
            w+=abs(b[(i+j)%n+1]-m);
            b[(i+j+1)%n+1]+=b[(i+j)%n+1]-m;
            b[(i+j)%n+1]=m;
        }
        s=min(s,w);
    }
    printf("%d",s);
    return 0;
}