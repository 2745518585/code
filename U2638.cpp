#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=10001;
int n;
ll k,f[N][N][2];
struct str
{
    ll l,r;
}a[N];
bool cmp(str a,str b)
{
    return a.r-a.l>b.r-b.l;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&a[i].l,&a[i].r);
        k=max(k,a[i].l);
    }
    for(int i=1;i<=n;++i)
    {
        a[i].l-=k,a[i].r-=k;
    }
    if(n%2==0) a[++n]=(str){0,0};
    sort(a+1,a+n+1,cmp);
    for(int i=0;i<=n;++i)
    {
        for(int j=0;j<=n;++j)
        {
            f[i][j][0]=f[i][j][1]=1e18;
        }
    }
    f[0][0][0]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=i;++j)
        {
            for(int l=0;l<=1;++l)
            {
                if(j<=i-l-1) f[i][j][l]=f[i-1][j][l]-a[i].l+(i-j-l-1)*(a[i].r-a[i].l);
                if(j>=1) f[i][j][l]=min(f[i][j][l],f[i-1][j-1][l]+a[i].r+(j-1)*(a[i].r-a[i].l));
            }
            f[i][j][1]=min(f[i][j][1],f[i-1][j][0]+(ll)(a[i].r-a[i].l)*(n/2));
        }
    }
    ll s=1e18;
    for(int i=0;i<=n;++i)
    {
        s=min(s,f[n][i][1]);
    }
    printf("%lld",s);
    return 0;
}