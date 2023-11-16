#include<bits/stdc++.h>
using namespace std;
const int N=16,M=20;
int n,a[N+1],b[N+1][5],g[N+1];
char f[1<<N][M+1];
void init()
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(b[j][3]==b[i][1]&&b[j][2]<=b[i][4]&&b[j][4]>=b[i][2])
            {
                g[i]|=(1<<(j-1));
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d%d%d",&b[i][1],&b[i][2],&b[i][3],&b[i][4],&a[i]);
    }
    init();
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=1;j<=M;++j)
        {
            f[i][j]=100;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(g[i]==0) f[1<<(i-1)][a[i]]=1;
    }
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=1;j<=M;++j)
        {
            for(int k=1;k<=n;++k)
            {
                if((i&(1<<(k-1)))!=0||(i&g[k])!=g[k]) continue;
                f[i|(1<<(k-1))][a[k]]=min(f[i|(1<<(k-1))][a[k]],(char)(f[i][j]+(j!=a[k])));
            }
        }
    }
    char s=100;
    for(int i=1;i<=M;++i)
    {
        s=min(s,f[(1<<n)-1][i]);
    }
    printf("%d",s);
    return 0;
}