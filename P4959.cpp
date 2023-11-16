#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100001;
int n;
ll f[N];
struct point
{
    ll x,y;
}a[N];
bool cmp(point a,point b)
{
    return a.x<b.x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld%lld",&a[i].x,&a[i].y);
        a[i].x=abs(a[i].x);
        a[i].y=abs(a[i].y);
    }
    for(int i=1;i<=n;++i)
    {
        bool u=false;
        for(int j=1;j<=n;++j)
        {
            if(i!=j&&a[i].x<=a[j].x&&a[i].y<=a[j].y)
            {
                u=true;
                break;
            }
        }
        if(u==true)
        {
            for(int j=i+1;j<=n;++j) a[j-1]=a[j];
            --n;
            --i;
        }
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i)
    {
        f[i]=1e18;
        for(int j=1;j<=i;++j)
        {
            f[i]=min(f[i],f[j-1]+a[i].x*a[j].y);
        }
    }
    printf("%lld",f[n]*4);
    return 0;
}