#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,t,a[N],mu[N];
ll mu2[N];
bool h[N];
ll check(int x,int y,int k)
{
    ll s=0;
    for(int i=1;i<=min(x,y);++i)
    {
        int j=min(x/(x/i),y/(y/i));
        s+=(ll)(mu2[j]-mu2[i-1])*(x/k/i)*(y/k/i);
        i=j;
    }
    return s;
}
int main()
{
    mu[1]=1;
    for(int i=2;i<=100000;++i)
    {
        if(h[i]==false) a[++t]=i,mu[i]=-1;
        for(int j=1;j<=t&&i*a[j]<=100000;++j)
        {
            h[i*a[j]]=true;
            if(i%a[j]==0) break;
            mu[i*a[j]]=-mu[i];
        }
    }
    for(int i=1;i<=100000;++i) mu2[i]=mu2[i-1]+mu[i];
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int a,b,c,d,k;
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
        printf("%lld\n",check(b,d,k)-check(a-1,d,k)-check(b,c-1,k)+check(a-1,c-1,k));
    }
    return 0;
}