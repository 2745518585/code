#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,a[N];
ll q,w=1e18,b[N],c[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        q+=a[i];
    }
    for(int i=1;i<=n;++i)
    {
        a[i]-=q/n;
        b[i]=b[i-1]+a[i];
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;++i)
    {
        c[1]+=abs(b[1]-b[i]);
    }
    int t1=1,t2=n-1;
    for(int i=2;i<=n;++i)
    {
        c[i]=c[i-1]+(t1-t2)*(b[i]-b[i-1]);
        ++t1,--t2;
    }
    for(int i=1;i<=n;++i)
    {
        w=min(w,c[i]);
    }
    printf("%lld",w);
    return 0;
}