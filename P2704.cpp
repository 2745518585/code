#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,a[101],f[101][2001][2001];
int sum(int x)
{
    int s=0;
    while(x!=0)
    {
        ++s;
        x-=(x&-x);
    }
    return s;
}
bool check(int x)
{
    return (x&(x<<1))!=0||(x&(x<<2))!=0||(x&(x>>1))!=0||(x&(x>>2))!=0;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("\n");
        for(int j=1;j<=m;++j)
        {
            char c=getchar();
            if(c=='P') a[i]=(a[i]<<1);
            else if(c=='H') a[i]=(a[i]<<1)+1;
        }
    }
    for(int i=0;i<=(1<<m)-1;++i)
    {
        if((a[1]&i)!=0||check(i)) continue;
        f[1][i][0]=sum(i);
    }
    for(int i=0;i<=(1<<m)-1;++i)
    {
        if((a[2]&i)!=0||check(i)) continue;
        for(int j=0;j<=(1<<m)-1;++j)
        {
            if((a[1]&j)!=0||(i&j)!=0||check(j)) continue;
            f[2][i][j]=max(f[2][i][j],f[1][j][0]+sum(i));
        }
    }
    for(int i=3;i<=n;++i)
    {
        for(int j=0;j<=(1<<m)-1;++j)
        {
            if((a[i]&j)!=0||check(j)) continue;
            for(int k=0;k<=(1<<m)-1;++k)
            {
                if((a[i-1]&k)!=0||(j&k)!=0||check(k)) continue;
                for(int l=0;l<=(1<<m)-1;++l)
                {
                    if((a[i-2]&l)!=0||(j&l)!=0||(k&l)!=0||check(l)) continue;
                    f[i][j][k]=max(f[i][j][k],f[i-1][k][l]+sum(j));
                }
            }
        }
    }
    int s=0;
    for(int i=0;i<=(1<<m)-1;++i)
    {
        for(int j=0;j<=(1<<m)-1;++j)
        {
            s=max(s,f[n][i][j]);
        }
    }
    printf("%d",s);
    return 0;
}
