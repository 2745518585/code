#include<cstdio>
#include<algorithm>
using namespace std;
const int p=1e8;
int m,n,a[21],f[21][10001];
bool check(int x)
{
    return (x&(x<<1))||(x&(x>>1));
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x;
            scanf("%d",&x);
            a[i]=(a[i]<<1)+x;
        }
        a[i]=~a[i];
    }
    for(int i=0;i<=(1<<n)-1;++i)
    {
        if(check(i)||(i&a[1])) continue;
        f[1][i]=1;
    }
    for(int i=2;i<=m;++i)
    {
        for(int j=0;j<=(1<<n)-1;++j)
        {
            if(check(j)||(j&a[i])) continue;
            for(int k=0;k<=(1<<n)-1;++k)
            {
                if(check(k)||(k&a[i-1])||(j&k)) continue;
                f[i][j]=(f[i][j]+f[i-1][k])%p;
            }
        }
    }
    int s=0;
    for(int i=0;i<=(1<<n)-1;++i) s=(s+f[m][i])%p;
    printf("%d",s);
    return 0;
}