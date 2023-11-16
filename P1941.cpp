#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001,M=10001;
int n,m,k,q,a[N][2],b[N][2],c[N],f[M],g[M];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i][0],&a[i][1]);
    }
    for(int i=1;i<=k;++i)
    {
        int x;
        scanf("%d%d%d",&x,&b[i][0],&b[i][1]);
        c[x]=i;
    }
    f[0]=g[0]=1e9;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            g[j]=f[j];
            f[j]=1e9;
        }
        for(int j=1;j<=m;++j)
        {
            f[min(j+a[i][0],m)]=min(f[min(j+a[i][0],m)],g[j]+1);
        }
        for(int j=1;j<=m;++j)
        {
            f[min(j+a[i][0],m)]=min(f[min(j+a[i][0],m)],f[j]+1);
        }
        for(int j=1;j<=m-a[i][1];++j)
        {
            f[j]=min(f[j],g[j+a[i][1]]);
        }
        if(c[i]!=0)
        {
            for(int j=1;j<=b[c[i]][0];++j) f[j]=1e9;
            for(int j=b[c[i]][1];j<=m;++j) f[j]=1e9;
            bool u=false;
            for(int j=b[c[i]][0]+1;j<=b[c[i]][1]-1;++j)
            {
                if(f[j]<1e9)
                {
                    u=true;
                    break;
                }
            }
            if(u==false)
            {
                printf("0\n%d",q);
                return 0;
            }
            ++q;
        }
    }
    int s=1e9;
    for(int i=1;i<=m;++i)
    {
        s=min(s,f[i]);
    }
    printf("1\n%d",s);
    return 0;
}