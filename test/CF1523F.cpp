#include<cstdio>
#include<algorithm>
using namespace std;
const int N=14,M=101;
int n,m,f[1<<N][M],g[1<<N][M],h1[1<<N][M],h2[1<<N][M];
struct str
{
    int x,y,t;
}a[M],b[M];
int dis(str a,str b)
{
    return abs(a.x-b.x)+abs(a.y-b.y);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&b[i].x,&b[i].y,&b[i].t);
    }
    sort(b+1,b+m+1,[&](str a,str b){return a.t<b.t;});
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=(1<<n)-1;++j)
        {
            h1[j][i]=1e9;
            for(int k=1;k<=n;++k)
            {
                if(j&(1<<(k-1))) h1[j][i]=min(h1[j][i],dis(a[i],a[k]));
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=0;j<=(1<<n)-1;++j)
        {
            h2[j][i]=1e9;
            for(int k=1;k<=n;++k)
            {
                if(j&(1<<(k-1))) h2[j][i]=min(h2[j][i],dis(b[i],a[k]));
            }
        }
    }
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=0;j<=m;++j) f[i][j]=1e9,g[i][j]=-1e9;
    }
    for(int i=1;i<=n;++i) f[1<<(i-1)][0]=0;
    for(int i=1;i<=m;++i) g[0][i]=1;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=1;j<=m;++j)
        {
            for(int k=0;k<=m;++k)
            {
                if(f[i][k]+h2[i][j]<=b[j].t) g[i][j]=max(g[i][j],k+1);
            }
            for(int k=1;k<=j-1;++k)
            {
                if(b[k].t+dis(b[j],b[k])<=b[j].t) g[i][j]=max(g[i][j],g[i][k]+1);
            }
            if(g[i][j]>=0) f[i][g[i][j]]=min(f[i][g[i][j]],b[j].t);
        }
        for(int j=1;j<=n;++j)
        {
            if(i&(1<<(j-1))) continue;
            for(int k=1;k<=m;++k)
            {
                if(g[i][k]>=0) f[i|(1<<(j-1))][g[i][k]]=min(f[i|(1<<(j-1))][g[i][k]],b[k].t+dis(b[k],a[j]));
            }
            for(int k=0;k<=m;++k)
            {
                f[i|(1<<(j-1))][k]=min(f[i|(1<<(j-1))][k],f[i][k]+h1[i][j]);
            }
        }
    }
    int s=0;
    for(int i=0;i<=(1<<n)-1;++i)
    {
        for(int j=0;j<=m;++j)
        {
            if(f[i][j]<1e9) s=max(s,j);
        }
        for(int j=1;j<=m;++j)
        {
            s=max(s,g[i][j]);
        }
    }
    printf("%d",s);
    return 0;
}