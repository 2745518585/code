#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2001,M=100001;
int n,m,q;
ll f[M];
struct str
{
    int c,f,v;
}a[N<<1];
bool cmp(str a,str b)
{
    if(a.f!=b.f) return a.f>b.f;
    return a.v<b.v;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&a[i].c,&a[i].f,&a[i].v);
        q+=a[i].c;
        a[i].v=-a[i].v;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&a[n+i].c,&a[n+i].f,&a[n+i].v);
    }
    sort(a+1,a+n+m+1,cmp);
    for(int i=0;i<=q;++i) f[i]=-1e18;
    f[0]=0;
    for(int i=1;i<=n+m;++i)
    {
        if(a[i].v<0)
        {
            for(int j=q;j>=a[i].c;--j)
            {
                f[j]=max(f[j],f[j-a[i].c]+a[i].v);
            }
        }
        else
        {
            for(int j=0;j<=q-a[i].c;++j)
            {
                f[j]=max(f[j],f[j+a[i].c]+a[i].v);
            }
        }
    }
    ll s=-1e18;
    for(int i=0;i<=q;++i)
    {
        s=max(s,f[i]);
    }
    printf("%lld",s);
    return 0;
}