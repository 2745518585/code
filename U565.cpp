#include<bits/stdc++.h>
using namespace std;
const int N=21;
int m,n,a[N][N],b[N][N],f[1<<N],g[1<<N];
int sum(int x,int y,int t)
{
    int dx=1,dy=n+1;
    for(int i=0;i<=y;++i)
    {
        if((x&(1<<i))!=0) --dy;
        else ++dx;
    }
    if(t==0) return a[dx][dy];
    else return b[dx][dy];
}
int sum2(int x)
{
    int s=0;
    while(x) x-=(x&-x),++s;
    return s;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[m-i+1][n-j+1]);
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&b[m-i+1][n-j+1]);
        }
    }
    for(int i=0;i<=(1<<(m+n))-1;++i) f[i]=-1e9;
    f[(1<<n)-1]=0;
    g[(1<<n)-1]=1-(m*n)%2;
    for(int i=0;i<=(1<<(m+n))-1;++i)
    {
        if(sum2(i)!=n) continue;
        for(int j=0;j<=m+n-2;++j)
        {
            if((i&(1<<j))!=0&&(i&(1<<(j+1)))==0)
            {
                #define X i^(1<<j)^(1<<(j+1))
                g[X]=g[i]^1;
                if(g[i]==0) f[X]=max(f[X],(-f[i]+sum(i,j,0)));
                else f[X]=max(f[X],(-f[i]+sum(i,j,1)));
                #undef X
            }
        }
    }
    printf("%d",f[((1<<n)-1)<<m]);
    return 0;
}