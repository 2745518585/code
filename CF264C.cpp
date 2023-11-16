#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001;
int n,m,a[N],b[N];
ll f[N],g[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        ll x,y;
        scanf("%lld%lld",&x,&y);
        ll w=0,q=0,w2=0,q2=0,s=0;
        for(int j=1;j<=n;++j) g[j]=-1e18;
        for(int j=1;j<=n;++j)
        {
            f[j]=max(g[b[j]]+x*a[j],(q!=b[j]?w:w2)+y*a[j]);
            if(f[j]>w)
            {
                if(b[j]!=q) w2=w,q2=q,w=f[j],q=b[j];
                else w=f[j],q=b[j];
            }
            else if(f[j]>w2&&b[j]!=q) w2=f[j],q2=b[j];
            g[b[j]]=max(g[b[j]],f[j]);
            s=max(s,f[j]);
        }
        printf("%lld\n",s);
    }
    return 0;
}