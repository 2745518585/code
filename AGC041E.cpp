#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;
const int N=50001,M=1000001;
int n,m,t,b[M],c[M];
bool g[M],h[M];
struct str
{
    int x,y;
}a[M];
bitset<N> f[N];
int main()
{
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    if(t==1)
    {
        for(int i=1;i<=n;++i) f[i][i]=1;
        for(int i=1;i<=m;++i)
        {
            f[a[i].x]=f[a[i].y]=f[a[i].x]|f[a[i].y];
        }
        int x=0;
        for(int i=1;i<=n;++i)
        {
            if(f[i].count()==n)
            {
                x=i;
                break;
            }
        }
        if(x==0)
        {
            printf("-1");
            return 0;
        }
        h[x]=true;
        for(int i=m;i>=1;--i)
        {
            if(h[a[i].x]) g[i]=true;
            h[a[i].x]=h[a[i].y]=h[a[i].x]|h[a[i].y];
        }
        for(int i=1;i<=m;++i)
        {
            if(g[i]) printf("^");
            else printf("v");
        }
    }
    else
    {
        if(n==2)
        {
            printf("-1");
            return 0;
        }
        for(int i=1;i<=n;++i) b[i]=i,c[i]=1;
        for(int i=m;i>=1;--i)
        {
            if(c[b[a[i].x]]==n-1)
            {
                ++c[b[a[i].y]];
                --c[b[a[i].x]];
                b[a[i].x]=b[a[i].y];
                g[i]=false;
            }
            else
            {
                ++c[b[a[i].x]];
                --c[b[a[i].y]];
                b[a[i].y]=b[a[i].x];
                g[i]=true;
            }
        }
        for(int i=1;i<=m;++i)
        {
            if(g[i]) printf("^");
            else printf("v");
        }
    }
    return 0;
}