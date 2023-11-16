#include<cstdio>
#include<algorithm>
using namespace std;
int n,f[61][300001];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        f[x][i]=i+1;
    }
    int s=0;
    for(int i=1;i<=60;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(f[i][j]==0) f[i][j]=f[i-1][f[i-1][j]];
            if(f[i][j]!=0) s=i;
        }
    }
    printf("%d",s);
    return 0;
}