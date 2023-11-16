#include<cstdio>
#include<algorithm>
using namespace std;
const int N=300001,M=21;
int n,m,q,f[N][M],g[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++g[x];
    }
    for(int i=1;i<=m;++i) g[i]+=g[i-1];
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=m;++j)
        {
            if(j+(1<<i)-1<=m) f[j][i]=f[j][i-1]^f[j+(1<<(i-1))][i-1]^(((g[j+(1<<i)-1]-g[j+(1<<(i-1))-1])&1)<<(i-1));
        }
    }
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int s=0,w=0;
        for(int j=20;j>=0;--j)
        {
            if(((y-x+1)&(1<<j))!=0)
            {
                s=s^f[x][j]^(((g[x+(1<<j)-1]-g[x-1])&1)*w);
                w^=(1<<j);
                x+=(1<<j);
            }
        }
        if(s) printf("A");
        else printf("B");
    }
    return 0;
}