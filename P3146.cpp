#include<cstdio>
#include<algorithm>
using namespace std;
int n,f[301][301];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&f[i][i]);
    }
    int s=0;
    for(int i=1;i<=n-1;++i)
    {
        for(int j=1;j<=n-i;++j)
        {
            for(int k=j;k<i+j;++k)
            {
                if(f[j][k]==f[k+1][i+j]&&f[j][k]!=0) f[j][i+j]=max(f[j][i+j],f[j][k]+1);
            }
            s=max(s,f[j][i+j]);
        }
    }
    printf("%d",s);
    return 0;
}