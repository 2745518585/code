#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,q,k,a[N],f1[N],f2[N];
ll m,b[N],c[N];
int main()
{
    scanf("%d%lld%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
        c[++q]=b[i];
    }
    sort(c+1,c+q+1);
    q=unique(c+1,c+q+1)-c-1;
    c[0]=-2e18,c[q+1]=3e18;
    for(int i=1;i<=n;++i)
    {
        b[i]=lower_bound(c+1,c+q+1,b[i])-c;
        ++a[b[i]];
    }
    for(int i=1;i<=q+1;++i) a[i]+=a[i-1];
    f1[0]=0;
    for(int i=1;i<=q;++i)
    {
        f1[i]=f1[i-1];
        while(a[i]-a[f1[i]]>=k) ++f1[i];
    }
    f2[q+1]=q+1;
    for(int i=q;i>=1;--i)
    {
        f2[i]=f2[i+1];
        while(a[f2[i]-1]-a[i-1]>=k) --f2[i];
    }
    ll s=0,w=0;
    for(ll x=0;x<=min(2ll,c[1]-1);++x)
    {
        ll x1=((c[f1[0]]+1)+x+1)/2,x2=(x+(c[f2[1]]-1))/2;
        x1=max(x1,0ll),x2=min(x2,m);
        // printf("%lld:%lld %lld\n",x,x1,x2);
        if(x2-x1+1>s)
        {
            s=x2-x1+1;
            w=x;
        }
    }
    for(int i=1;i<=q;++i)
    {
        {
            ll x=c[i];
            ll x1=((c[f1[i]]+1)+x+1)/2,x2=(x+(c[f2[i]]-1))/2;
            x1=max(x1,0ll),x2=min(x2,m);
            // printf("%lld:%lld %lld\n",c[i],x1,x2);
            if(x2-x1+1>s)
            {
                s=x2-x1+1;
                w=x;
            }
        }
        for(ll x=c[i]+1;x<=min(c[i]+2,c[i+1]-1);++x)
        {
            ll x1=((c[f1[i]]+1)+x+1)/2,x2=(x+(c[f2[i+1]]-1))/2;
            x1=max(x1,0ll),x2=min(x2,m);
            // printf("%lld:%lld %lld\n",x,x1,x2);
            if(x2-x1+1>s)
            {
                s=x2-x1+1;
                w=x;
            }
        }
        for(ll x=max(c[i]+1,c[i+1]-2);x<=c[i+1]-1;++x)
        {
            ll x1=((c[f1[i]]+1)+x+1)/2,x2=(x+(c[f2[i+1]]-1))/2;
            x1=max(x1,0ll),x2=min(x2,m);
            // printf("%lld:%lld %lld\n",x,x1,x2);
            if(x2-x1+1>s)
            {
                s=x2-x1+1;
                w=x;
            }
        }
    }
    printf("%lld %lld\n",s,w);
    return 0;
}