#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=3001;
const ll P=1e9+7;
int n,m,k,op,b[N],f[N][N],h[N];
ll g[N][N];
struct str
{
    int l,r,w;
}a[N];
void check(int &x1,ll &y1,int x2,ll y2)
{
    if(x2>x1) x1=x2,y1=y2;
    else if(x1==x2) y1=(y1+y2)%P;
}
bool cmp(str a,str b)
{
    if(a.l!=b.l) return a.l<b.l;
    return a.r<b.r;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&k,&op);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&a[i].w,&a[i].l,&a[i].r);
        ++h[a[i].l],--h[a[i].r+1];
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=m;++i) h[i]+=h[i-1];
    for(int i=1;i<=m;++i) b[i]=b[i-1]+(h[i]==0);
    for(int i=1;i<=n;++i)
    {
        a[i].l-=b[a[i].l];
        a[i].r-=b[a[i].r];
    }
    m-=b[m];
    if(op==0)
    {
        int x=1,s=0;
        for(int i=1;i<=n;++i)
        {
            while(x<=n&&h[x]==0) ++x;
            if(x<a[i].l) ++s,x=a[i-1].r+1;
            while(x<=n&&h[x]==0) ++x;
            if(a[i].w<=k) x=min(x+(k-a[i].w),a[i].r+1);
            else x=a[i].r+1,++s;
        }
        while(x<=n&&h[x]==0) ++x;
        if(x<n+1) ++s;
        printf("%d",n-s);
        return 0;
    }
    for(int i=0;i<=n+1;++i)
    {
        for(int j=0;j<=m+1;++j) f[i][j]=-1e9;
    }
    f[1][1]=0;
    g[1][1]=1;
    for(int i=1;i<=n;++i)
    {
        if(a[i].w<=k)
        {
            for(int j=a[i].l;j<=a[i].r-(k-a[i].w);++j)
            {
                check(f[i+1][j+(k-a[i].w)],g[i+1][j+(k-a[i].w)],f[i][j]+1,g[i][j]);
            }
            for(int j=a[i].r-(k-a[i].w)+1;j<=a[i].r;++j)
            {
                check(f[i+1][a[i].r+1],g[i+1][a[i].r+1],f[i][j]+1,g[i][j]);
            }
        }
        for(int j=a[i].l;j<=a[i].r;++j)
        {
            check(f[i+1][a[i].r+1],g[i+1][a[i].r+1],f[i][j],g[i][j]);
        }
        for(int j=a[i].r+1;j<=m;++j)
        {
            check(f[i+1][j],g[i+1][j],f[i][j]+(a[i].w<=k),g[i][j]);
        }
    }
    for(int i=1;i<=n;++i) check(f[i+1][m+1],g[i+1][m+1],f[i][m+1]+(a[i].w<=k),g[i][m+1]);
    printf("%d %lld",f[n+1][m+1],g[n+1][m+1]);
    return 0;
}