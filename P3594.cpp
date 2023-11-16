#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,m,Q[N],T,R;
ll k,a[N];
int main()
{
    scanf("%d%lld%d",&n,&k,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        a[i]+=a[i-1];
    }
    int s=m,x=m;
    T=1,R=0;
    Q[++R]=m;
    for(int i=m;i<=n;++i)
    {
        while(T<=R&&Q[T]<=i-1) ++T;
        while(x<=n&&(a[x]-a[i-m])-(a[Q[T]]-a[Q[T]-m])<=k)
        {
            s=max(s,x-(i-m));
            ++x;
            if(x<=n)
            {
                while(T<=R&&a[Q[R]]-a[Q[R]-m]<=a[x]-a[x-m]) --R;
                Q[++R]=x;
            }
        }
    }
    printf("%d",s);
    return 0;
}