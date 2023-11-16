#include<bits/stdc++.h>
using namespace std;
const int N=500001,M=10,p[5][5]={{0,2,2,2,2},{2,1,3,4,3},{2,3,1,3,4},{2,4,3,1,3},{2,3,4,3,1}};
int n,f[M][M],g[M][M];
int main()
{
    scanf("%d\n",&n);
    for(int i=0;i<=4;++i)
    {
        for(int j=0;j<=4;++j)
        {
            f[i][j]=1e9;
        }
    }
    f[0][0]=0;
    for(int i=1;i<=n;++i)
    {
        int a=getchar()-'0';
        for(int j=0;j<=4;++j)
        {
            for(int k=0;k<=4;++k)
            {
                g[j][k]=f[j][k];
                f[j][k]=1e9;
            }
        }
        for(int j=0;j<=4;++j)
        {
            for(int k=0;k<=4;++k)
            {
                if(k!=a) f[a][k]=min(f[a][k],g[j][k]+p[j][a]);
                if(j!=a) f[j][a]=min(f[j][a],g[j][k]+p[k][a]);
            }
        }
    }
    int s=1e9;
    for(int i=0;i<=4;++i)
    {
        for(int j=0;j<=4;++j)
        {
            s=min(s,f[i][j]);
        }
    }
    printf("%d",s);
    return 0;
}