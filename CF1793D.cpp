#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a1[N],a2[N],b1[N],b2[N];
ll sum(ll x,ll y)
{
    if(x>y) return 0;
    return (y-x+1)*(y-x+2)/2;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a1[i]);
        b1[a1[i]]=i;
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a2[i]);
        b2[a2[i]]=i;
    }
    ll s=sum(1,min(b1[1],b2[1])-1)+sum(max(b1[1],b2[1])+1,n)+sum(min(b1[1],b2[1])+1,max(b1[1],b2[1])-1);
    int x=min(b1[1],b2[1]),y=max(b1[1],b2[1]);
    for(int i=2;i<=n;++i)
    {
        int z1=min(b1[i],b2[i]),z2=max(b1[i],b2[i]);
        if(b1[i]<x&&b2[i]<x) s+=(ll)(x-z2)*(n-y+1);
        else if(b1[i]>y&&b2[i]>y) s+=(ll)(x)*(z1-y);
        else if(z1<x&&z2>y) s+=(ll)(x-z1)*(z2-y);
        x=min(x,z1),y=max(y,z2);
    }
    printf("%lld",s+1);
    return 0;
}