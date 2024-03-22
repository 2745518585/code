#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,b1[N],b2[N],f[N];
char a[N],c[N];
ll sum(ll x,ll y)
{
    return (x+y)*((y-x)/2+1)/2;
}
void solve()
{
    for(int i=0;i<=n*2+3;++i) f[i]=0;
    for(int i=n;i>=1;--i)
    {
        c[i*2]=a[i];
        c[i*2-1]='#';
    }
    c[n*2+1]='#';
    c[0]='~';
    c[n*2+2]='@';
    int x=1,s=0;
    for(int i=1;i<=n*2+1;++i)
    {
        if(i<=x+f[x]-1) f[i]=min(f[x*2-i],x+f[x]-i);
        while(c[i+f[i]]==c[i-f[i]]) ++f[i];
        if(i+f[i]>x+f[x]) x=i;
        s=max(s,f[i]);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%s",&n,&m,a+1);
        solve();
        for(int i=0;i<=n+1;++i) b1[i]=b2[i]=0;
        for(int i=2;i<=n;++i)
        {
            if(a[i-1]!=a[i]) ++b1[i];
        }
        for(int i=3;i<=n;++i)
        {
            if(a[i-2]!=a[i]) ++b2[i];
        }
        for(int i=1;i<=n;++i) b1[i]+=b1[i-1],b2[i]+=b2[i-1];
        for(int i=1;i<=m;++i)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            int t=r-l+1;
            ll s=0;
            if(b1[r]-b1[l]>0)
            {
                s+=sum(2,((t-1)/2)*2);
            }
            if(b2[r]-b2[l+1]>0)
            {
                s+=sum(3,(t/2-1)*2+1);
            }
            if(f[l+r]<r-l+1)
            {
                s+=t;
            }
            printf("%lld\n",s);
        }
    }
    return 0;
}