#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=1e9+7;
int n,q,b[N],b1[N],b2[N];
ll f[N],g[N];
struct str
{
    int x,a;
}a[N];
struct str2
{
    int x,l,r;
}d[N];
bool cmp(str a,str b)
{
    return a.x<b.x;
}
bool cmp2(str2 a,str2 b)
{
    return a.x<b.x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].a,&a[i].x);
        b[++q]=a[i].a;
    }
    sort(b+1,b+n+1);
    q=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i].a=lower_bound(b+1,b+q+1,a[i].a)-b;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i) d[i].x=a[i].a;
    for(int i=1;i<=n;++i)
    {
        if(b1[a[i].a]==0)
        {
            for(int j=a[i].a;j>=1&&b1[j]==0;--j) b1[j]=i;
        }
        d[i].l=b1[a[i].a];
    }
    for(int i=n;i>=1;--i)
    {
        if(b2[a[i].a]==0)
        {
            for(int j=a[i].a;j<=q&&b2[j]==0;++j) b2[j]=i;
        }
        d[i].r=b2[a[i].a];
    }
    sort(d+1,d+n+1,cmp2);
    f[0]=g[0]=1;
    int x=0;
    for(int i=1;i<=n;++i)
    {
        while(d[x].r<d[i].l-1) ++x;
        f[i]=(g[i-1]-g[x-1])%P;
        g[i]=(g[i-1]+f[i])%P;
    }
    while(d[x].r<n) ++x;
    printf("%lld",((g[n]-g[x-1])%P+P)%P);
    return 0;
}