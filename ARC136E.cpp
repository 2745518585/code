#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,a[N],b[N];
ll f[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=2;i<=n;++i)
    {
        if(b[i]!=0) continue;
        b[i]=i;
        for(int j=1;i*j<=n;++j)
        {
            if(b[i*j]==0) b[i*j]=i;
        }
    }
    for(int i=2;i<=n;++i)
    {
        if(i%2==0)
        {
            f[i]+=a[i];
            f[i+1]-=a[i];
        }
        else
        {
            f[i-b[i]+1]+=a[i];
            f[i+b[i]]-=a[i];
        }
    }
    for(int i=2;i<=n;++i) f[i]+=f[i-1];
    ll s=0;
    for(int i=2;i<=n;++i) s=max(s,f[i]);
    printf("%lld",s+a[1]);
    return 0;
}