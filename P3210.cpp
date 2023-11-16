#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,b1[N],b2[N];
ll a[N];
bool h[N];
int main()
{
    scanf("%d",&n);
    ll w=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        h[i]=a[i]!=0;
        w+=a[i];
        b1[i]=i-1;
        b2[i]=i+1;
    }
    b2[0]=1;
    b1[n+1]=n;
    for(int i=3;i<=n;i=b2[i])
    {
        while(h[i]&&h[b1[i]]&&h[b1[b1[i]]]&&a[b1[b1[i]]]<=a[b1[i]]&&a[b1[i]]>=a[i])
        {
            a[i]=a[b1[b1[i]]]+a[i]-a[b1[i]];
            b1[i]=b1[b1[b1[i]]];
            b2[b1[i]]=i;
        }
    }
    int x=b2[0],y=b1[n+1];
    ll t=0;
    while(a[x]>=a[b2[x]]&&h[x]&&h[b2[x]]) t+=a[b2[x]]-a[x],x=b2[b2[x]];
    while(a[y]>=a[b1[y]]&&h[y]&&h[b1[y]]) t+=a[b1[y]]-a[y],y=b1[b1[y]];
    for(int i=x;i<=y;i=b2[i])
    {
        if(a[i]!=0) a[++q]=a[i];
    }
    sort(a+1,a+q+1,[&](ll x,ll y){return x>y;});
    a[++q]=t;
    ll s=0;
    for(int i=1;i<=q;++i)
    {
        if(i%2==1) s+=a[i];
        else s-=a[i];
    }
    printf("%lld %lld",(w+s)/2,(w-s)/2);
    return 0;
}