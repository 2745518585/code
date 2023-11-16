#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],b[N];
int solve(int k)
{
    int m=0;
    for(int i=1;i<=n;++i)
    {
        if(i==k) continue;
        b[++m]=a[i]%a[k];
    }
    sort(b+1,b+m+1);
    int s=(b[m]+b[m-1])%a[k],x=m;
    for(int i=1;i<=m;++i)
    {
        while(x>=1&&b[i]+b[x]>=a[k]) --x;
        if(x!=0) s=max(s,b[i]+b[x]);
    }
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    int s=0;
    for(int i=n;i>=1;--i)
    {
        if(a[i]-1<=s) break;
        if(a[i]==a[i+1]) continue;
        s=max(s,solve(i));
    }
    printf("%d",s);
    return 0;
}