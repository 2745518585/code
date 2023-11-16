#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,m,k,t,a[N],b[N];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    t=n-m+1;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    rotate(a+1,a+k%n+1,a+n+1);
    for(int i=m;i<=n;++i) b[i-m+1]=a[i];
    if(k>t)
    {
        rotate(b+1,b+(t-k%t)%t+1,b+t+1);
        k=t;
    }
    bool u=true;
    for(int i=1;i<=m-2;++i)
    {
        if(a[i]>=a[i+1]) u=false;
    }
    for(int i=1;i<=k;++i)
    {
        if(a[1]<=b[t-i+1]) u=false;
    }
    if(!u)
    {
        printf("0");
        return 0;
    }
    ll s=1;
    for(int i=1;i<=m-1;++i) s=s*i%P;
    int z=0;
    for(int i=t-k+1;i<=t;++i)
    {
        if(z<b[i]) z=b[i],s=s*m%P;
    }
    printf("%lld",s);
    return 0;
}
