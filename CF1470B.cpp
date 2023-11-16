#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,m,fa[N],h[N];
ll a[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    for(ll i=1;i<=1000000;++i) fa[i]=i;
    for(ll i=2;i<=1000000;++i)
    {
        for(ll j=1;i*i*j<=1000000;++j)
        {
            fa[find(i*i*j)]=find(j);
        }
    }
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
            h[find(a[i])]=0;
        }
        int s1=0,s2=0,s3=0;
        for(int i=1;i<=n;++i)
        {
            ++h[find(a[i])];
            s1=max(s1,h[find(a[i])]);
        }
        for(int i=1;i<=n;++i)
        {
            if(find(a[i])==1||h[find(a[i])]%2==0) ++s2;
            else s3=max(s3,h[find(a[i])]);
        }
        scanf("%d",&m);
        for(int i=1;i<=m;++i)
        {
            ll x;
            scanf("%lld",&x);
            if(x==0) printf("%d\n",s1);
            else printf("%d\n",max(s2,s3));
        }
    }
    return 0;
}