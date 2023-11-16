#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll k,a[N],f[N];
int main()
{
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n*2;++i) f[i]=0;
    ll w=0,t=0,s=0;
    for(int i=n;i>=1;--i)
    {
        w-=t;
        t-=f[i+k];
        a[i]-=w;
        if(a[i]>0&&i>=k)
        {
            f[i]=(a[i]-1)/k+1;
            a[i]-=f[i]*k;
            t+=f[i];
            s+=f[i];
            w+=f[i]*k;
        }
    }
    ll p=0;
    for(int i=1;i<=k-1;++i)
    {
        if(a[i]>0) p=max(p,(a[i]-1)/i+1);
    }
    printf("%lld\n",s+p);
    return 0;
}