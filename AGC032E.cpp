#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,a[N];
bool check(int x)
{
    for(int i=x+1;i<=n;++i)
    {
        if(a[i]+a[n+x+1-i]<m) return false;
    }
    return true;
}
int main()
{
    scanf("%d%d",&n,&m);
    n*=2;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        a[i]%=m;
    }
    sort(a+1,a+n+1);
    int l=0,r=n/2;
    while(l<r)
    {
        int z=l+r>>1;
        if(check(z*2)) r=z;
        else l=z+1;
    }
    int s=0;
    for(int i=1;i<=l*2;++i) s=max(s,a[i]+a[l*2+1-i]);
    for(int i=l*2+1;i<=n;++i) s=max(s,a[i]+a[n+l*2+1-i]-m);
    printf("%d",s);
    return 0;
}