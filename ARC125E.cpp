#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,e[N];
ll a[N],b[N],c[N];
bool cmp(int x,int y)
{
    return c[x]/b[x]<c[y]/b[y];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%lld",&b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%lld",&c[i]);
    }
    for(int i=1;i<=m;++i) e[i]=i;
    sort(e+1,e+m+1,cmp);
    sort(a+1,a+n+1);
    ll w=0;
    for(int i=1;i<=n;++i) w+=a[i];
    ll q=0;
    for(int i=1;i<=m;++i) q+=b[i];
    ll s=w;
    int x=1;
    for(int i=n;i>=1;--i)
    {
        w-=a[i];
        while(x<=n&&b[e[x]]*(n-i+1)>c[e[x]])
        {
            q-=b[e[x]];
            w+=c[e[x]]-b[e[x]]*(n-i);
            ++x;
        }
        w+=q;
        s=min(s,w);
    }
    printf("%lld",s);
    return 0;
}