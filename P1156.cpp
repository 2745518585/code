#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,q,f[100001];
struct str
{
    int t,a,b;
}a[10001];
bool cmp(str a,str b)
{
    return a.t<b.t;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&a[i].t,&a[i].a,&a[i].b);
        q+=a[i].a;
    }
    q+=10;
    sort(a+1,a+n+1,cmp);
    f[0]=10;
    for(int i=1;i<=n;++i)
    {
        for(int j=m;j>=0;--j)
        {
            if(f[j]<a[i].t) continue;
            if(j+a[i].b>=m)
            {
                printf("%d",a[i].t);
                return 0;
            }
            f[j+a[i].b]=max(f[j+a[i].b],f[j]);
            f[j]+=a[i].a;
        }
    }
    int s=10;
    for(int i=1;i<=n;++i)
    {
        if(s+a[i-1].t<a[i].t)
        {
            printf("%d",a[i-1].t+s);
            return 0;
        }
        s=s-(a[i].t-a[i-1].t)+a[i].a;
    }
    printf("%d",a[n].t+s);
    return 0;
}