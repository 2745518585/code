#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,t,a[N],phi[N];
bool h[N];
int main()
{
    scanf("%d",&n);
    phi[1]=1;
    for(int i=2;i<=n;++i)
    {
        if(h[i]==false) a[++t]=i,phi[i]=i-1;
        for(int j=1;j<=t&&i*a[j]<=n;++j)
        {
            h[i*a[j]]=true;
            if(i%a[j]==0)
            {
                phi[i*a[j]]=phi[i]*a[j];
                break;
            }
            phi[i*a[j]]=phi[i]*(a[j]-1);
        }
    }
    ll s=0;
    for(int i=1;i<=n;++i)
    {
        s+=(ll)phi[i]*(n/i)*(n/i);
    }
    printf("%lld",(s-(ll)n*(n+1)/2)/2);
    return 0;
}