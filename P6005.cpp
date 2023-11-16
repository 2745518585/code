#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001,M=2001;
int n,m,q,s=-1e9,p=1,t[N],b[N],f[N][N];
struct road
{
    int m,q;
}a[M];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
    }
    for(int i=1;i<=n;++i) f[i][0]=-1e9;
    f[1][0]=0;
    for(int i=1;i<=500;++i)
    {
        for(int j=1;j<=n;++j) f[j][i]=-1e9;
        for(int j=1;j<=n;++j)
        {
            for(int k=t[j];k!=0;k=a[k].q)
            {
                f[a[k].m][i]=max(f[a[k].m][i],f[j][i-1]+b[a[k].m]);
            }
        }
    }
    for(int i=0;i<=500;++i)
    {
        s=max(s,f[1][i]-q*i*i);
    }
    printf("%d",s);
    return 0;
}