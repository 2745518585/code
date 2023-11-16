#include<bits/stdc++.h>
using namespace std;
const int N=1001;
int n,f[N][N];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<=n*2;++i)
    {
        for(int j=0;j<=n;++j)
        {
            f[i][j]=1e9;
        }
    }
    f[0][0]=0;
    for(int i=0;i<=n-1;++i)
    {
        for(int j=0;j<=i;++j)
        {
            f[i+1][j]=min(f[i+1][j],f[i][j]+1);
            f[i][i]=min(f[i][i],f[i][j]+5);
            f[i+j][j]=min(f[i+j][j],f[i][j]+2);
        }
    }
    int s=1e9;
    for(int i=n;i<=n*2;++i)
    {
        for(int j=0;j<=n;++j)
        {
            s=min(s,f[i][j]);
        }
    }
    printf("%d",s);
    return 0;
}