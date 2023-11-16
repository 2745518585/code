#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=251,M=31;
int n,m,t,k,b[N];
struct str
{
    int x,s,y;
}c[N];
bool cmp(str a,str b)
{
    return a.x<b.x;
}
struct matrix
{
    int m,n;
    ll a[N][N];
    matrix(){}
    matrix(int _m,int _n,int x)
    {
        m=_m,n=_n;
        if(x==0) for(int i=1;i<=m;++i) for(int j=1;j<=n;++j) a[i][j]=-1e18;
        if(x==1) for(int i=1;i<=m;++i) for(int j=1;j<=n;++j) a[i][j]=0;
    }
    friend matrix operator*(matrix a,matrix b)
    {
        matrix c(a.m,b.n,0);
        for(int i=1;i<=c.m;++i)
        {
            for(int j=1;j<=c.n;++j)
            {
                for(int k=1;k<=a.n;++k)
                {
                    c.a[i][j]=max(c.a[i][j],a.a[i][k]+b.a[k][j]);
                }
            }
        }
        return c;
    }
}a[M];
int main()
{
    scanf("%d%d%d%d",&n,&m,&t,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    a[0]=matrix(n*5,n*5,0);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        a[0].a[x][n*(w-1)+y]=b[y];
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=4;++j) a[0].a[n*j+i][n*(j-1)+i]=0;
    }
    for(int i=1;i<=30;++i) a[i]=a[i-1]*a[i-1];
    for(int i=1;i<=k;++i)
    {
        scanf("%d%d%d",&c[i].x,&c[i].s,&c[i].y);
    }
    sort(c+1,c+k+1,cmp);
    matrix x(1,n*5,0);
    x.a[1][1]=b[1];
    for(int i=1;i<=k;++i)
    {
        int z=c[i].x-c[i-1].x;
        for(int j=30;j>=0;--j)
        {
            if(z>=(1<<j)) x=x*a[j],z-=(1<<j);
        }
        x.a[1][c[i].s]+=c[i].y;
    }
    int z=t-c[k].x;
    for(int j=30;j>=0;--j)
    {
        if(z>=(1<<j)) x=x*a[j],z-=(1<<j);
    }
    printf("%lld",x.a[1][1]<0?-1:x.a[1][1]);
    return 0;
}