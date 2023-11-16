#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[201],b[201],f1[201][201],f2[201][201],g1[201][201];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        a[n+i]=a[i];
        g1[i][i]=i;
        g1[n+i][n+i]=n+i;
    }
    for(int i=1;i<=n*2;++i)
    {
        b[i]=b[i-1]+a[i];
    }
    for(int i=n*2;i>=1;--i)
    {
        for(int j=i+1;j<=min(i+n-1,n*2);++j)
        {
            f1[i][j]=1e9;
            f2[i][j]=max(f2[i][j-1],f2[i+1][j])+b[j]-b[i-1];
            for(int k=g1[i][j-1];k<=g1[i+1][j];++k)
            {
                if(f1[i][k]+f1[k+1][j]+b[j]-b[i-1]<f1[i][j])
                {
                    f1[i][j]=f1[i][k]+f1[k+1][j]+b[j]-b[i-1];
                    g1[i][j]=k;
                }
            }
        }
    }
    int s1=1e9,s2=0;
    for(int i=1;i<=n;++i)
    {
        s1=min(s1,f1[i][i+n-1]);
        s2=max(s2,f2[i][i+n-1]);
    }
    printf("%d\n%d",s1,s2);
    return 0;
}