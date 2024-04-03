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
    for(int i=1;i<=m;++i) b[i]+=(h[i]==0);
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
        for(int j=0;j<=n+1;++j) f[i][j]=-1e9;
    }
    f[0][0]=0;
    g[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=i-1;++j)
        {
            if(f[i-1][j]<a[i].l-1) continue;
            if(f[i-1][j]>a[i].r)
            {
                check(f[i][j+(a[i].w<=k)],g[i][j+(a[i].w<=k)],f[i-1][j],g[i-1][j]);
                continue;
            }
            if(a[i].w<=k) check(f[i][j+1],g[i][j+1],min(f[i-1][j]+(k-a[i].w),a[i].r),g[i-1][j]);
            check(f[i][j],g[i][j],a[i].r,g[i-1][j]);
        }
    }
    for(int i=n;i>=0;--i)
    {
        if(f[n][i]==n)
        {
            printf("%d %lld",i,g[n][i]);
            return 0;
        }
    }
    return 0;
}