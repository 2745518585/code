#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m;
ll a[N],b[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    ll s1=0,s2=0;
    for(int i=2;i<=m*2;++i)
    {
        for(int j=1;j<=n;++j) b[j]=a[j]%i;
        sort(b+1,b+n+1);
        b[n+1]=1e9;
        for(int j=0;j<=n;++j)
        {
            if((n-j)%2==1)
            {
                ll l=max(b[j],b[n-1]/2)+1,r=min(b[j+1],(ll)m);
                s1+=max(min(r,i-l)-max(l,i-r)+1,0ll);
            }
            else
            {
                ll l=max(b[j],b[n]/2)+1,r=min(b[j+1],(ll)m);
                s2+=max(min(r,i-l)-max(l,i-r)+1,0ll);
            }
        }
    }
    printf("%lld %lld %lld %lld\n",((ll)m*m-s1-s2)/2,((ll)m*m-s1-s2)/2,s1,s2);
    return 0;
}