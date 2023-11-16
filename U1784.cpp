#include<bits/stdc++.h>
using namespace std;
const int N=201;
int n,m,f[N][N][N];
int main()
{
    scanf("%d%d",&n,&m);
    f[0][0][1]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            for(int k=1;k<=i;++k)
            {
                for(int l=1;l<=k;++l)
                {
                    f[i][j][k]+=f[i-k][j-1][l];
                }
            }
        }
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        s+=f[n][m][i];
    }
    printf("%d",s);
    return 0;
}